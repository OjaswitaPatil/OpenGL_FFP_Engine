#include "globalHeaders.h"

//opengl related libraries
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib, "GLU32.lib")

// macros
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

// global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// global variable declrations
// variables realted with fulll screen
BOOL gbFullScreen = FALSE;  
HWND ghwnd = NULL;  
DWORD dwStyle;
WINDOWPLACEMENT wpPrev;

// variables realated with file I/O
char gszLogFileName[] = "Log.txt";
FILE *gpFile = NULL;

// active window related varibale
BOOL gbActiveWindow = FALSE;

// exit key press realted
BOOL gbEscapeKeyIsPress = FALSE;

// opengl related global variables
HDC ghdc = NULL;
HGLRC ghrc = NULL;

// Rotation angles
float angleTriangle = 0.0f;
float angleRectangle = 0.0f;

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
    gpFile = fopen(gszLogFileName, "w");
    if(gpFile == NULL)
    {
        MessageBox(NULL, TEXT("Log file createion failed"), TEXT("ERROR"), MB_OK);
        exit(0);
    }
    else
    {
        fprintf(gpFile, "Program Started Successfully\n");
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
        fprintf(gpFile, "Initialize () failed\n");
        DestroyWindow(hwnd);
        hwnd = NULL;
    }
    else
    {
        fprintf(gpFile, "initialize() completed successfully \n");
    }

    // SET THIS WINDOW AS FORGROUND AND ACTIVE WINDOW
    SetForegroundWindow(hwnd);
    SetFocus(hwnd);

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
        break;

        case WM_CLOSE:
        uninitialize();
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
        ShowCursor(FALSE);
    }
    else
    {
        SetWindowPlacement(ghwnd, &wpPrev);
        SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
        SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);
        ShowCursor(TRUE);
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

    // getdc
    ghdc = GetDC(ghwnd);
    if(ghdc == NULL)
    {
        fprintf(gpFile, "getDC fun failed\n");
        return(-1);
    }
  
    //get matching pixel foremat idex using hdc and pfd
    iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);
    if(iPixelFormatIndex == 0)
    {
        fprintf(gpFile, "choose pixel format failed\n");
        return -2;
    }

    // select the pixel format of found index
    if(SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
    {
        fprintf(gpFile, "set pixel format fun failed\n");
        return -3;
    }

    //create rendering context using hdc ,pfd, and chosen pixel format inedx
    ghrc = wglCreateContext(ghdc);
    if(ghrc == NULL)
    {
        fprintf(gpFile, "wglCreateContext fun failed\n");
        return -4;
    }

    // make this rendering contex as current contex
    if(wglMakeCurrent(ghdc, ghrc) == FALSE)
    {
        fprintf(gpFile, " wglMakeCurrent fun failed\n");
        return -5;
    }

    // print gl info
    printGLInfo();

    // from here onwards openGL code starts
    // tell opengl to choose the color to clear the screen
    glClearColor(0.0f, 0.0f, 0.0f,1.0f);

    // warm up resize
    resize(WIN_WIDTH, WIN_HEIGHT);

    return(0);
}

void printGLInfo(void)
{
    // code
    // print opengl information
    fprintf(gpFile,"OpenGL Information\n");
    fprintf(gpFile,"******************\n");
    fprintf(gpFile,"OpenGL Vender : %s\n", glGetString(GL_VENDOR));
    fprintf(gpFile,"OpenGL Renderer : %s\n", glGetString(GL_RENDERER));
    fprintf(gpFile,"OpenGL Version : %s\n", glGetString(GL_VERSION));
    fprintf(gpFile,"******************\n");
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
    //code
    // clear opengl buffers
    glClear(GL_COLOR_BUFFER_BIT);

    // TRIANGLE

    // set matrix to model view mode
    glMatrixMode(GL_MODELVIEW);

    // SEt to identity matrix
    glLoadIdentity(); 

    // translate triangle baclwaord b y Z
    glTranslatef(-1.5f, 0.0f, -6.0f);
    glRotatef(angleTriangle, 0.0f, 1.0f, 0.0f);

    // drawing code of triangle
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();

    // RECTANGLE

    // SEt to identity matrix
    glLoadIdentity(); 

    // translate triangle backword x y Z
    glTranslatef(1.5f, 0.0f, -6.0f);
    glRotatef(angleRectangle, 1.0f, 0.0f, 0.0f);

    // drawing code of triangle
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();

    // swap the buffers
    SwapBuffers(ghdc);
}

void update(void)
{
    // code
    angleTriangle = angleTriangle + 0.05f;
    if(angleTriangle >= 360.0f)
    {
        angleTriangle = angleTriangle - 360.0f;
    }

    angleRectangle = angleRectangle - 0.05f;
    if(angleRectangle <= 0.0f)
    {
        angleRectangle = angleRectangle + 360.0f;
    }
}

void uninitialize(void)
{
    // FUN DECLRATIONS
    void togglFullScreen(void);
    //code

    // if is existing in FS then restore to back
    if(gbFullScreen == TRUE)
    {
        toggleFullScreen();
        gbFullScreen = FALSE;
    }
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
        fprintf(gpFile,"Program terminated successfully\n");
        fclose(gpFile);
        gpFile = NULL;
    }
}


