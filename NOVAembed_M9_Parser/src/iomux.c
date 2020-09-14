#include "../include/NOVAembed_M9_parser.h"

iomux_cfg       *iomux;
iomux_spi       *spi;
iomux_i2c2      *i2c2;

void dump_iomux(void)
{
    printf("\nPeripherals usage ( 1 means IN USE ):\n");
    printf("**********************************************\n");
    printf("spi      : %d spidev %d\n",iomux->spi,iomux->spi_dev);
    printf("i2c3     : %d\n",iomux->i2c3);
    printf("i2c6     : %d\n",iomux->i2c6);
    printf("uart2    : %d\n",iomux->uart2);
    printf("uart4    : %d\n",iomux->uart4);
    printf("hdmi     : %d\n",iomux->hdmi);
    printf("edp      : %d\n",iomux->edp);
    printf("dsi      : %d\n",iomux->dsi);
    printf("spdif    : %d\n",iomux->spdif);
    printf("pcm      : %d\n",iomux->pcm);
    printf("pcie     : %d\n",iomux->pcie);
    printf("cam0     : %d\n",iomux->cam0);
    printf("cam1     : %d\n",iomux->cam1);
    printf("**********************************************\n\n");
}

void copy_and_resize(char *dest,char *source)
{
char *dup = strdup(source);
int i;
    *index(dup,0x0a)=0;
    if ( strlen(dup)<10)
    {
        if (( dup[0] == '0' ) && (dup[1] == 'x' ))
            dup += 2;
        sprintf(dest,"%8s", dup);
        for(i=0;i<8;i++)
            if ( dest[i] == ' ')
                dest[i]='0';
    }
    else
        snprintf(dest,9,"%s",dup+2);
}

void parse_iomux(void)
{
    iomux = calloc(1,sizeof(iomux_cfg));

    if ( strstr(file_contents,"M9_GPIO2_B1_comboBox=SDA6"))
    {
        iomux->i2c6 = 1;
    }
    if ( strstr(file_contents,"M9_GPIO4_C0_comboBox=SDA3"))
    {
        iomux->i2c3 = 1;
    }
    if ( strstr(file_contents,"M9_GPIO1_B0_comboBox=SPI1_TXD"))
    {
        iomux->spi = 1;
    }
    if ( strstr(file_contents,"M9_SPIdev_checkBox=true"))
    {
        iomux->spi_dev = 1;
    }
    if ( strstr(file_contents,"M9_GPIO1_B0_comboBox=UART4_TX"))
    {
        iomux->uart4 = 1;
    }
    if ( strstr(file_contents,"M9_GPIO4_C0_comboBox=UART2_TX"))
    {
        iomux->uart2 = 1;
    }

    if ( strstr(file_contents,"M9_HDMI_checkBox=true"))
    {
        iomux->hdmi = 1;
    }
    if ( strstr(file_contents,"M9_eDP_checkBox=true"))
    {
        iomux->edp = 1;
    }
    if ( strstr(file_contents,"M9_DSI_checkBox=true"))
    {
        iomux->dsi = 1;
    }
    if ( strstr(file_contents,"M9_SPDIF_checkBox=true"))
    {
        iomux->spdif = 1;
    }
    if ( strstr(file_contents,"M9_GPIO4_A4_comboBox=LRCK_RX"))
    {
        iomux->pcm = 1;
    }
    if ( strstr(file_contents,"M9_PCIE_checkBox=true"))
    {
        iomux->pcie = 1;
    }
    if ( strstr(file_contents,"M9_Cam1_checkBox=true"))
    {
        iomux->cam0 = 1;
    }
    if ( strstr(file_contents,"M9_Cam2_checkBox=true"))
    {
        iomux->cam1 = 1;
    }
    if ( strstr(file_contents,"M9_WiFi_checkbox=true"))
    {
        iomux->wifi = 1;
    }
    if ( strstr(file_contents,"M9_Bt_checkbox=true"))
    {
        iomux->bt = 1;
    }

}

