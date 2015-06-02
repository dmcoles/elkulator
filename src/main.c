/*Elkulator v1.0 by Tom walker
  Initialisation/Closing/Main loop*/
#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "elk.h"
#include "elkulator-config.h"
#undef printf
int autoboot;
FILE *rlog;
void rpclog(char *format, ...)
{
   char buf[256];
   return;
   if (!rlog) rlog=fopen("e:/devcpp/cycleelk/rlog.txt","wt");
//turn;
   va_list ap;
   va_start(ap, format);
   vsprintf(buf, format, ap);
   va_end(ap);
   fputs(buf,rlog);
   fflush(rlog);
}

/*int waiting,waiting2;

void waitforthread()
{
        return;
        waiting=1;
        while (!waiting2)
              sleep(10);
}

void stopwaiting()
{
        waiting=0;
}*/

int drawit=0;
void drawitint()
{
        drawit++;
}

void cleardrawit()
{
        drawit=0;
}

/*void wait50()
{
//        if (!infocus) drawit=1;
        if (tapeon && tapespeed) drawit=1;
        while (!drawit || !infocus)
        {
                sleep(1);
//                if (waiting) return;
        }
        drawit--;
}*/

char tapename[512];

static void showUsage()
{
    char executablePath[_MAX_PATH_WITH_NULL];
    get_executable_name(executablePath, COUNTOF(executablePath));
    char const *fileName = get_filename(executablePath);

    printf("Elkulator " ELKULATOR_VERSION " command line options\n\n");
    printf("Usage: %s <options>\n", fileName);
    printf("  --conf CONF_FILE_NAME         Specify configuration file name\n");
    printf("  --resource-dir RESOURCE_DIR   Specify resource directory\n");
    printf("  -disc SSD_FILE_NAME           Load SSD disc image into drives 0/2\n");
    printf("  -disc1 SSD_FILE_NAME          Load SSD disc image into drives 1/3\n");
    printf("  -tape UEF_FILE_NAME           Load UEF tape image\n");
    printf("  -debug                        Start debugger\n");
    exit(-1);
}

void initelk(int argc, char *argv[])
{
        char tempFileName[_MAX_PATH_WITH_NULL];
        int c;
        char *p;
        int tapenext=0,discnext=0;
        get_executable_name(exedir,511);
        p=get_filename(exedir);
        p[0]=0;
        discname[0]=discname2[0]=tapename[0]=0;
//        printf("Load config\n");

        c = 1;
        if (c < argc - 1 && strcasecmp(argv[c], "--conf") == 0)
        {
            ++c;
            strcpy(tempFileName, argv[c]);
            ++c;
        }
        else
        {
            if (!pathJoin(
                exedir,
                "elk.cfg",
                tempFileName,
                COUNTOF(tempFileName)))
            {
                printf("! pathJoin failed\n");
                abort();
            }
        }

        if (!pathResolve(
            tempFileName,
            g_configurationFileName,
            COUNTOF(g_configurationFileName),
            NULL))
        {
            printf("! pathResolve failed\n");
            abort();
        }

        loadconfig();

        strcpy(g_resourceDir, exedir);

//printf("commandline\n");

        for (; c < argc; ++c)
        {
//printf("%i\n",c); fflush(stdout);
//                printf("%i : %s\n",c,argv[c]);
/*                if (!strcasecmp(argv[c],"-1770"))
                {
                        I8271=0;
                        WD1770=1;
                }
                else*/
#ifndef WIN32
                if (!strcasecmp(argv[c],"--help"))
                {
                    showUsage();
                    exit(0);
                }
                else
#endif
                if (!strcasecmp(argv[c], "--resource-dir"))
                {
                    if (++c >= argc)
                    {
                        printf("! Invalid command line!\n");
                        abort();
                    }

                    strcpy(tempFileName, argv[c]);

                    if (!pathResolve(
                        tempFileName,
                        g_resourceDir,
                        COUNTOF(g_resourceDir),
                        NULL))
                    {
                        printf("! pathResolve failed\n");
                        abort();
                    }
                }
                else if (!strcasecmp(argv[c],"-tape"))
                {
                        tapenext=2;
                }
                else if (!strcasecmp(argv[c],"-disc") || !strcasecmp(argv[c],"-disk"))
                {
                        discnext=1;
                }
                else if (!strcasecmp(argv[c],"-disc1"))
                {
                        discnext=2;
                }
                else if (!strcasecmp(argv[c],"-debug"))
                {
                        debug=debugon=1;
                }
                else if (tapenext)
                   strcpy(tapename,argv[c]);
                else if (discnext)
                {
                        if (discnext==2) strcpy(discname2,argv[c]);
                        else             strcpy(discname,argv[c]);
                        discnext=0;
                }
                if (tapenext) tapenext--;
        }

//printf("initalmain\n"); fflush(stdout);

        initalmain(0,NULL);
//printf("loadroms\n"); fflush(stdout);
        loadroms();
//printf("reset6502\n");
        reset6502();
        initula();
        resetula();
        reset1770();
        
        loadtape(tapename);
        loaddisc(0,discname);
        loaddisc(1,discname2);
        if (defaultwriteprot) writeprot[0]=writeprot[1]=1;
#ifndef WIN32
        install_keyboard();
#endif
        install_timer();
        install_int_ex(drawitint,MSEC_TO_TIMER(20));
        install_joystick(JOY_TYPE_AUTODETECT);
        inital();
        initsound();
        loaddiscsamps();
        maketapenoise();

        makekeyl();
        
        set_display_switch_mode(SWITCH_BACKGROUND);
        
//        initresid();
//        resetsid();
//        setsidtype(0,0);
}

int ddnoiseframes=0;
int oldf12=0;
int resetit=0;
int runelkframe=0;
void runelk()
{
        int c;
        if (drawit || (tapeon && tapespeed))
        {
                if (drawit) drawit--;
                if (drawit>8 || drawit<0) drawit=0;
                for (c=0;c<312;c++) exec6502();
                if (runelkframe) exec6502();
                runelkframe=!runelkframe;
                if (resetit)
                {
                        memset(ram,0,32768);
                        resetula();
                        reset6502();
                        resetit=0;
                }
                if (key[KEY_F12] && !oldf12)
                {
                        reset6502();
                }
                oldf12=key[KEY_F12];
                if (wantloadstate) doloadstate();
                if (wantsavestate) dosavestate();
                if (infocus) poll_joystick();
                if (autoboot) autoboot--;
                ddnoiseframes++;
                if (ddnoiseframes>=5)
                {
                        ddnoiseframes=0;
                        mixddnoise();
                }
        }
        else
           rest(1);
}

void closeelk()
{
        saveconfig();
//        dumpram();
//        dumpregs();
//        printf("Closing!\n");
}
