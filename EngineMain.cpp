#include "globalHeaders.h"
#include "EngineMain.h"
#include "Models.h"
#include "linkedList.h"
#include "ImGUIHelper.h"
#include "TextRendering.h"
#include "Texture.h"

//opengl related libraries
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib, "GLU32.lib")

// macros
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

struct ScreenRotate screenRotate;

// global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// global variable declrations
// variables realted with fulll screen
BOOL gbFullScreen = FALSE;
DWORD dwStyle;
WINDOWPLACEMENT wpPrev;
HWND ghwnd = NULL;


// active window related varibale
BOOL gbActiveWindow = FALSE;

// exit key press realted
BOOL gbEscapeKeyIsPress = FALSE;

// opengl related global variables
HDC ghdc = NULL;
HGLRC ghrc = NULL;

//###imgui###
// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
//############

// ENTRY POINT FUNCTION
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
    // function declarations
    int initialize(void);
    void display(void);
    void update(void);
    void uninitialize(void);

    // variable declarations
    WNDCLASSEX wndclass;
    HWND hwnd;
    MSG msg;
    TCHAR szAppName[] = TEXT("RTR6");
    BOOL bDone = FALSE;

    // code
    // create log file
    int logResult = init_logging(gszLogFileName);
    if(logResult <= 0)
    {
        exit(0);
    }
    else
    {
        LOG_DEBUG("*************Winmain() started ***********");
        LOG_INFO("Winmain() -> Log file created successfully !!!");
    }



    // window class initialization
    wndclass.cbSize = sizeof(WNDCLASSEX);
    wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.lpfnWndProc = WndProc;
    wndclass.hInstance = hInstance;
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.lpszClassName = szAppName;
    wndclass.lpszMenuName = NULL;
    wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

    // registration of window class
    RegisterClassEx(&wndclass);

    // create window
    hwnd = CreateWindowEx(
        WS_EX_APPWINDOW,
        szAppName,
        TEXT("OJASWITA PATIL"),
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        WIN_WIDTH,
        WIN_HEIGHT,
        NULL,
        NULL,
        hInstance,
        NULL
    );
    ghwnd = hwnd;

    //show window
    ShowWindow(hwnd, iCmdShow);

    // paint the background of window
    UpdateWindow(hwnd);

    // initialize
    int result = initialize();
    if(result != 0)
    {
        LOG_ERROR("Winmain() -> Initialize () failed");
        DestroyWindow(hwnd);
        hwnd = NULL;
    }
    else
    {
        LOG_INFO("Winmain() -> initialize() completed successfully ");
    }

    // SET THIS WINDOW AS FORGROUND AND ACTIVE WINDOW
    SetForegroundWindow(hwnd);
    SetFocus(hwnd);

    // set ImGUI context
    setupImGUIContext();

    // game loop
    while(bDone == FALSE)
    {
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if(msg.message == WM_QUIT)
            {
                bDone = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            if(gbActiveWindow == TRUE)
            {
                if(gbEscapeKeyIsPress == TRUE)
                {
                    bDone = TRUE;
                }
                //render
                display();

                // update
                update();
            }

        }
    }

    // uninitialize
    uninitialize();

    return((int)msg.wParam);
}

// callback function
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    // function declarations
    void toggleFullScreen(void);
    void resize(int, int);
    void uninitialize(void);

    // ### imgui ###
    if (ImGui_ImplWin32_WndProcHandler(hwnd, iMsg, wParam, lParam))
        return true;

    // code
    switch(iMsg)
    {
        case WM_CREATE:
        ZeroMemory((void *)&wpPrev, sizeof(WINDOWPLACEMENT));
        wpPrev.length = sizeof(WINDOWPLACEMENT);
        break;

        case WM_SETFOCUS:
        gbActiveWindow = TRUE;
        break;

        case WM_KILLFOCUS:
        gbActiveWindow = FALSE;
        break;

        case WM_ERASEBKGND:
        return(0);

        case WM_SIZE:
        resize(LOWORD(lParam), HIWORD(lParam));
        break;

        case WM_KEYDOWN:
        //Check for multikey press
        if(GetAsyncKeyState(VK_CONTROL) & 0x8000)//ctrl is pressed
        {
            switch(wParam)
            {
                case 'F':
                case 'f':
                if(gbFullScreen == FALSE)
                {
                    toggleFullScreen();
                    gbFullScreen = TRUE;
                }
                else
                {
                    toggleFullScreen();
                    gbFullScreen = FALSE;
                }
                break;

                default:
                break;
            }
        }

        switch(wParam)
        {
            case VK_ESCAPE:
            gbEscapeKeyIsPress = TRUE;
            break;

            default:
            break;
        }
        break;

        case WM_CHAR:
        switch(wParam)
        {
            //Add keys here

            default:
            break;
        }
        break;

        case WM_CLOSE:
        gbEscapeKeyIsPress = TRUE;
        break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            break;
    }
    return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void toggleFullScreen(void)
{
    // variable declarations
     MONITORINFO mi;

    // code
    if(gbFullScreen == FALSE)
    {
        dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
        if(dwStyle & WS_OVERLAPPEDWINDOW)  // CHECK aapli stayle overlapped ahe ka
        {
            ZeroMemory((void *)&mi, sizeof(MONITORINFO));
            mi.cbSize = sizeof(MONITORINFO);
            if(GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
            {
                SetWindowLong(ghwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
                SetWindowPos(ghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_NOZORDER | SWP_FRAMECHANGED);
            }
        }
        // ShowCursor(FALSE);
    }
    else
    {
        SetWindowPlacement(ghwnd, &wpPrev);
        SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
        SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);
        // ShowCursor(TRUE);
    }
}

int initialize(void)
{
    // function declarations
    void printGLInfo(void);
    void resize(int, int);


    // variable declartions
    PIXELFORMATDESCRIPTOR pfd;
    int iPixelFormatIndex = 0;

    //code
    LOG_DEBUG("*************initialize() started ***********");

    // pixel format decription initialization
    ZeroMemory((void*)&pfd, sizeof(PIXELFORMATDESCRIPTOR));
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cRedBits = 8;
    pfd.cGreenBits = 8;
    pfd.cBlueBits = 8;
    pfd.cAlphaBits = 8;
    pfd.cDepthBits = 32;

    // getdc
    ghdc = GetDC(ghwnd);
    if(ghdc == NULL)
    {
        LOG_ERROR("initialize() -> GetDC() failed");
        return(-1);
    }
    else
    {
        LOG_DEBUG("initialize() -> GetDC() succeeded");
    }

    //get matching pixel foremat idex using hdc and pfd
    iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);
    if(iPixelFormatIndex == 0)
    {
        LOG_ERROR("initialize() -> ChoosePixelFormat() failed");
        return -2;
    }
    else
    {
        LOG_DEBUG("initialize() -> ChoosePixelFormat() succeeded");
    }

    // select the pixel format of found index
    if(SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
    {
        LOG_ERROR("initialize() -> SetPixelFormat() failed");
        return -3;
    }
    else
    {
        LOG_DEBUG("initialize() -> SetPixelFormat() succeeded");
    }

    //create rendering context using hdc ,pfd, and chosen pixel format inedx
    ghrc = wglCreateContext(ghdc);
    if(ghrc == NULL)
    {
        LOG_ERROR("initialize() -> wglCreateContext() failed");
        return -4;
    }
    else
    {
        LOG_DEBUG("initialize() -> wglCreateContext() succeeded");
    }

    // make this rendering contex as current contex
    if(wglMakeCurrent(ghdc, ghrc) == FALSE)
    {
        LOG_ERROR("initialize() -> wglMakeCurrent() failed");
        return -5;
    }
    else
    {
        LOG_DEBUG("initialize() -> wglMakeCurrent() succeeded");
    }

    // print gl info
    printGLInfo();

    // depth realted function call
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0f);                                                         // go in my depth buffer and set 1.0
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // from here onwards openGL code starts
    // tell opengl to choose the color to clear the screen
    glClearColor(0.0f, 0.0f, 0.0f,1.0f);

    // scrennRotate
    screenRotate.rotate.x = 9.0f;
    screenRotate.rotate.y = 12.0f;
    screenRotate.rotate.z = 0.0f;

    //load texture test
    addTextureNameToallTexturesArray("Stone.bmp");
    addTextureNameToallTexturesArray("Vijay_Kundali.bmp");
    addTextureNameToallTexturesArray("Smiley.bmp");
    addTextureNameToallTexturesArray("marble.bmp");

    //enable texturing
    glEnable(GL_TEXTURE_2D);

    LOG_DEBUG("*************initialize() Completed ***********");

    // createModel(TRIANGLE);
    // createModel(RECTANGLE);

    // warm up resize
    resize(WIN_WIDTH, WIN_HEIGHT);

    return(0);
}

void printGLInfo(void)
{
    // code
    LOG_DEBUG("*************printGLInfo() Started ***********");
    // print opengl information
    LOG_INFO("       OpenGL Information");
    LOG_INFO("       --------------------------");
    LOG_INFO("       OpenGL Vender : %s", glGetString(GL_VENDOR));
    LOG_INFO("       OpenGL Renderer : %s", glGetString(GL_RENDERER));
    LOG_INFO("       OpenGL Version : %s", glGetString(GL_VERSION));
    LOG_INFO("       --------------------------");
    LOG_DEBUG( "*************printGLInfo() Completed ***********");
}

void resize(int width, int height)
{
    //code
    if(height <= 0)
    {
        // if height by accient become 0 or less then 0 then make height 1
        height = 1;
    }

    // set the viewport
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);

    // set matrix projection mode
    glMatrixMode(GL_PROJECTION);    // MATRIX CHA MODE PROJECTION LA THEV

    //set to identity matrix
    glLoadIdentity();                // matrix la identitty matrix kr

    //do perspective projection
    gluPerspective
    (   45.0f, // FOV-Y   field of  view y
        (GLfloat)width / (GLfloat)height,  //aspect ratio
        0.1f,   //near
        100.0f  // far
    );
}

void display(void)
{
    // Start the ImGui frame
    startImGUIFrame();
    // Generate UI (Not rendering here)
    generateUI();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    {
        drawGridForEntireScene();

        drawAllModels();
    }
    glPopMatrix();

    //Render/display Generated UI
    renderGeneratedUI();

    SwapBuffers(ghdc);
}

void update(void)
{
    // code
}

void uninitialize(void)
{
    // FUN DECLRATIONS
    void togglFullScreen(void);

    //code
    LOG_DEBUG("*************uninitialize() Started ***********");

    // uninitialize ImGUI
    uninitializeImGUI();

    // if is existing in FS then restore to back
    if(gbFullScreen == TRUE)
    {
        toggleFullScreen();
        gbFullScreen = FALSE;
    }

    //delete allLoadedTextureArray
    for(int i = 0; i<numberOfTextureAvailablesinallTexturesArray; i++)
    {
        if(allLoadedTextureIdentifiers_Array[0])
        {
            glDeleteTextures(1, &allLoadedTextureIdentifiers_Array[0]);
            allLoadedTextureIdentifiers_Array[0] = 0;
        }
        free(allTextureNames_Array[i]);
    }
    free(allLoadedTextureIdentifiers_Array);
    free(allTextureNames_Array);

    // make hdc as current context by releasing rendering contex as current contex
    if(wglGetCurrentContext() == ghrc)
    {
        wglMakeCurrent(NULL, NULL);
    }

    // delete the rendering context
    if(ghrc)
    {
        wglDeleteContext(ghrc);
        ghrc = NULL;
    }

    // release the dc
    if(ghdc)
    {
        ReleaseDC(ghwnd, ghdc);
        ghdc = NULL;
    }

    // destroy window
    if(ghwnd)
    {
        DestroyWindow(ghwnd);
        ghwnd = NULL;
    }

    // close the file
    if(gpFile)
    {
        LOG_INFO("uninitialize() -> Program terminated successfully");
        LOG_DEBUG("*************uninitialize() completed ***********");
        LOG_DEBUG("*************Winmain() completed ***********");

        close_logging();
    }
}


