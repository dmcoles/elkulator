/*Elkulator v1.0 by Tom Walker
  Configuration file handling*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "elk.h"
#include "sideways_bank.h"

FILE *cfgfile;
char cfgbuffer[1024];
int sndex;
int sndint;
int firstbyte;
int defaultwriteprot;
int joffset;

char *getstringcfg(char *name)
{
        char *t;
        int c;
        int a,b;
        if (!cfgfile) return NULL;
//        rpclog("Looking for %s\n",name);
        fseek(cfgfile,0,SEEK_SET);
        while (1)
        {
                t = fgets(cfgbuffer, COUNTOF(cfgbuffer), cfgfile);
                //rpclog("New string - %s\n",cfgbuffer);
                if (!t) return 0;
                c=0;
                while (name[c] && cfgbuffer[c])
                {
                        a=toupper(name[c]);
                        b=toupper(cfgbuffer[c]);
                        if (a!=b) break;
                        c++;
                }
                if (name[c]) continue;

                // Verify that we're matching the whole of the key and not just a prefix
                if (cfgbuffer[c] != ' ' && cfgbuffer[c] != '=')
                {
                    continue;
                }

                if (!cfgbuffer[c]) continue;
//                rpclog("Matched - now %s\n",&cfgbuffer[c]);
                while (cfgbuffer[c] && cfgbuffer[c]!='=') c++;
                if (!cfgbuffer[c]) continue;
                c++;
//                rpclog("Found equals - now %s\n",&cfgbuffer[c]);
                while (cfgbuffer[c] && cfgbuffer[c]==' ') c++;
                if (!cfgbuffer[c]) continue;
                for (b=strlen(&cfgbuffer[c]);b>=0;b--)
                {
                        if (((char *)&cfgbuffer[c])[b]==13 || ((char *)&cfgbuffer[c])[b]==10)
                        {
                                ((char *)&cfgbuffer[c])[b]=0;
                                break;
                        }
                }
//                rpclog("Over! found %s\n",&cfgbuffer[c]);
                return &cfgbuffer[c];
        }
}

int getintcfg(char *name, int def)
{
        int c;
        char *s=getstringcfg(name);
        if (!s) return def;
//        rpclog("Returned string %s for %s\n",s,name);
        sscanf(s,"%i",&c);
//        rpclog("c is %i\n",c);
        return c;
}

void writestringcfg(char *name, char *s)
{
        if (s[0]) fprintf(cfgfile,"%s = %s\n",name,s);
}
void writeintcfg(char *name, int i)
{
        fprintf(cfgfile,"%s = %i\n",name,i);
}

static void loadSidewaysBankConfig()
{
    char *s;
    int i;
    char key[20];
    SidewaysBankInfo *sidewaysBank;
    char const *colonIndex;
    int typeLength;

    for (i = COUNTOF(g_sidewaysBanks) - 1; i >= 0; --i)
    {
        sidewaysBank = g_sidewaysBanks + i;

        sprintf(key, "sideways_bank_%X", i);
        s = getstringcfg(key);
        if (s == NULL)
        {
            sidewaysBank->type = SidewaysBankType_Empty;
            sidewaysBank->path[0] = '\0';
        }
        else
        {
            colonIndex = strchr(s, ':');
            typeLength = (int)(colonIndex - s);

            if (strncmp("empty", s, typeLength) == 0)
            {
                sidewaysBank->type = SidewaysBankType_Empty;
            }
            else if (strncmp("ram", s, typeLength) == 0)
            {
                sidewaysBank->type = SidewaysBankType_Ram;
            }
            else if (strncmp("rom", s, typeLength) == 0)
            {
                sidewaysBank->type = SidewaysBankType_Rom;
            }
            else
            {
                TRACE("! Unsupported sideways bank type '%.*s'\n", typeLength, s);
                abort();
            }

            strcpy(sidewaysBank->path, colonIndex + 1);
        }
    }
}

static void saveSidewaysBankConfig()
{
    int i;
    char key[20];
    char value[_MAX_PATH_WITH_NULL];

    for (i = COUNTOF(g_sidewaysBanks) - 1; i >= 0; --i)
    {
        char const *typeStr;
        switch (g_sidewaysBanks[i].type)
        {
        case SidewaysBankType_Empty: typeStr = "empty"; break;
        case SidewaysBankType_Ram: typeStr = "ram"; break;
        case SidewaysBankType_Rom: typeStr = "rom"; break;
        default:
            TRACE("! Invalid sideways bank type\n");
            abort();
        }

        sprintf(key, "sideways_bank_%X", i);
        sprintf(value, "%s:%s", typeStr, g_sidewaysBanks[i].path);
        writestringcfg(key, value);
    }
}

void loadconfig()
{
        char *s;
        int c;
        char s2[20];

        cfgfile = fopen(g_configurationFileName, "rt");
        if (cfgfile == NULL)
        {
            TRACE("! Failed to open configuration file %s\n", g_configurationFileName);
            return;
        }

        TRACE("! Loading settings from configuration file %s\n", g_configurationFileName);

        s = getstringcfg("os_rom_path");
        if (s != NULL)
        {
            strcpy(os_rom_path, s);
        }

        s = getstringcfg("mrb_os_rom_path");
        if (s != NULL)
        {
            strcpy(mrb_os_rom_path, s);
        }

        loadSidewaysBankConfig();

        tapespeed=getintcfg("tapespeed",0);
        plus1=getintcfg("plus1",0);
        plus3=getintcfg("plus3",0);
        dfsena=getintcfg("dfsena",0);
        adfsena=getintcfg("adfsena",0);
        defaultwriteprot=getintcfg("defaultwriteprotect",1);
        
        turbo=getintcfg("turbo",0);
        mrb=getintcfg("mrb",0);
        mrbmode=getintcfg("mrbmode",0);

        drawmode=getintcfg("filter",0);
        
        s=getstringcfg("discname_0");
        if (s)
        {
                strcpy(discname,s);
                loaddisc(0,discname);
        }
        else   discname[0]=0;
        s=getstringcfg("discname_1");
        if (s)
        {
                strcpy(discname2,s);
                loaddisc(1,discname2);
        }
        else   discname2[0]=0;

        sndint=getintcfg("sound_internal",1);
        sndex=getintcfg("sound_exp",0);
        sndddnoise=getintcfg("sound_ddnoise",1);
        ddvol=getintcfg("sound_ddvol",2);
        ddtype=getintcfg("sound_ddtype",1);
        sndtape=getintcfg("sound_tape",0);
        
        videoresize=getintcfg("win_resize",0);
        
        firstbyte=getintcfg("joy_firstbyte",0);
        
        joffset=getintcfg("joy_offset",0);

        for (c=0;c<128;c++)
        {
                sprintf(s2,"key_define_%03i",c);
                keylookup[c]=getintcfg(s2,c);
        }

        fclose(cfgfile);
}

void saveconfig()
{
        int c;
        char s[20];

        cfgfile = fopen(g_configurationFileName, "wt");
        if (cfgfile == NULL)
        {
            TRACE("! Failed to open configuration file %s\n", g_configurationFileName);
            return;
        }

        TRACE("! Saving settings to configuration file %s\n", g_configurationFileName);

        writestringcfg("os_rom_path", os_rom_path);
        writestringcfg("mrb_os_rom_path", mrb_os_rom_path);

        saveSidewaysBankConfig();

        writeintcfg("tapespeed",tapespeed);
        writeintcfg("plus1",plus1);
        writeintcfg("plus3",plus3);
        writeintcfg("dfsena",dfsena);
        writeintcfg("adfsena",adfsena);
        writeintcfg("defaultwriteprotect",defaultwriteprot);
        
        writestringcfg("discname_0",discname);
        writestringcfg("discname_1",discname2);

        writeintcfg("turbo",turbo);
        writeintcfg("mrb",mrb);
        writeintcfg("mrbmode",mrbmode);
        
        writeintcfg("filter",drawmode);
        
        writeintcfg("sound_internal",sndint);
        writeintcfg("sound_exp",sndex);

        writeintcfg("sound_ddnoise",sndddnoise);
        writeintcfg("sound_ddvol",ddvol);
        writeintcfg("sound_ddtype",ddtype);
        
        writeintcfg("sound_tape",sndtape);

        writeintcfg("win_resize",videoresize);
        
        writeintcfg("joy_firstbyte",firstbyte);
        
        writeintcfg("joy_offset",joffset);
        
        for (c=0;c<128;c++)
        {
                sprintf(s,"key_define_%03i",c);
                writeintcfg(s,keylookup[c]);
        }

        fclose(cfgfile);
}
