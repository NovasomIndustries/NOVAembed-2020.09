#include "../include/NOVAembed_M9_parser.h"
#include "../include/header.h"

char    dtsfile_dump[32768],dtsifile_dump[32768];
char    file_name[32],file_name_noext[32],dir_name[256];
char    file_name_dts[128],file_name_dtsi[128];
char    hog[1024];
char    gpio_hogs[2048];

int extract_speed(char *speed_var_ptr)
{
char    *duplicate;
    duplicate = strdup(speed_var_ptr);
    *index(duplicate,0x0a)=0;
    duplicate += strlen("M9_I2C2Speed=");
    return(atoi(duplicate));
}

void process_peripherals(void)
{
char    t[1024];
int     speed;

}

void create_dts_file(void)
{
FILE    *fpout_dts,*fpout_dtsi;
char    include_string[128],define_string[1024];

    printf("file_name_dts  : %s\n",file_name_dts );
    printf("file_name_dtsi : %s\n",file_name_dtsi);
    process_peripherals();

    sprintf(dtsfile_dump,dts_header);
    sprintf(include_string,"#include \"%s\"",file_name_dtsi);
    strcat(dtsfile_dump,include_string);
    strcat(dtsfile_dump,dts_footer);

    if ( (fpout_dts = fopen(file_name_dts,"w" ) ))
    {
        fwrite(dtsfile_dump, strlen(dtsfile_dump), 1, fpout_dts);
        fclose(fpout_dts);
    }
    else
        printf("DTS Write error\n");

    sprintf(dtsifile_dump,"/* #defines */\n");
    if (iomux->i2c3 == 1)
        strcat(dtsifile_dump,"#define HAS_I2C3\n");
    if (iomux->i2c6 == 1)
        strcat(dtsifile_dump,"#define HAS_I2C6\n");
    if (iomux->uart2 == 1)
        strcat(dtsifile_dump,"#define HAS_UART2\n");
    if (iomux->uart4 == 1)
        strcat(dtsifile_dump,"#define HAS_UART4\n");
    if (iomux->hdmi == 1)
        strcat(dtsifile_dump,"#define HAS_HDMI\n");
    if (iomux->edp == 1)
        strcat(dtsifile_dump,"#define HAS_EDP\n");
    if (iomux->dsi == 1)
        strcat(dtsifile_dump,"#define HAS_DSI\n");
    if (iomux->spdif == 1)
        strcat(dtsifile_dump,"#define HAS_SPDIF\n");
    if (iomux->pcm == 1)
        strcat(dtsifile_dump,"#define HAS_PCM\n");
    if (iomux->pcie == 1)
        strcat(dtsifile_dump,"#define HAS_PCIE\n");
    if (iomux->cam0 == 1)
        strcat(dtsifile_dump,"#define HAS_CAM0\n");
    if (iomux->cam1 == 1)
        strcat(dtsifile_dump,"#define HAS_CAM1\n");
    if (iomux->hdmi == 1)
        strcat(dtsifile_dump,"#define HAS_HDMI\n");

    strcat(dtsifile_dump,dtsi_header);

    //printf("After sprintf dts  is %s\n",dtsfile_dump);
    //printf("After sprintf dtsi is %s\n",dtsifile_dump);

    if ( (fpout_dtsi = fopen(file_name_dtsi,"w" ) ))
    {
        fwrite(dtsifile_dump, strlen(dtsifile_dump), 1, fpout_dtsi);
        fclose(fpout_dtsi);
    }
    else
        printf("DTSi Write error\n");
    //printf("%s\n",dtsifile_dump);
}

void create_file_names(char *file_in)
{
int     i;
    bzero(dtsfile_dump,sizeof(dtsfile_dump));

    sprintf(file_name,"%s",basename(strdup(file_in)));
    sprintf(dir_name,"%s",dirname(strdup(file_in)));

    sprintf(file_name_noext,"%s",file_name);
    if ( strlen(file_in) < 4 )
    {
        printf("File name %s is invalid\n",file_name);
        exit (-1);
    }
    for(i=0;i<strlen(file_name_noext);i++)
    {
        if ( file_name_noext[i] == '.')
            file_name_noext[i]=0;
    }
    sprintf(file_name_dts,"/Devel/NOVAsdk/DtbUserWorkArea/%s.dts",file_name_noext);
    sprintf(file_name_dtsi,"/Devel/NOVAsdk/DtbUserWorkArea/%s.dtsi",file_name_noext);


    printf("Input File Name       :  %s\n",file_in);
    printf("Output DTS  File Name : %s\n",file_name_dts);
    printf("Output DTSi File Name : %s\n",file_name_dtsi);
}

void store_dts_files(char *file_in)
{
    create_file_names(file_in);
    create_dts_file();
    printf("DTS  len : %d\n",(int )strlen(dtsfile_dump));
    printf("DTSi len : %d\n",(int )strlen(dtsifile_dump));
    dump_iomux();
}
