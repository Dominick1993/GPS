#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdbool.h>
#include "gpsbmp.h"

int main (int argc, char * argv[])
{
    /* ošetrenie argumentov */
    if (argc != 6)
    {
        fprintf(stderr,"Nespravny pocet parametrov\n");
        return (-1);
    }

    /* inicializacia allegro */
    al_init();
    al_init_image_addon();
    al_init_primitives_addon();

    /* ziskanie parametrov */
    int params[4];
    for(int i = 2; i<argc; i++) params[i-2] = stringToInt(argv[i]);

    /* nastavenie velkosti stran v pixeloch */
    int x = (params[3]-params[2])*60;
    int y = (params[1]-params[0])*60;

    ALLEGRO_BITMAP *bitmap = al_create_bitmap(abs(x),abs(y));
    if (bitmap == NULL){
        fprintf(stderr, "Nepodarilo sa vytvoriť bitmapu - al_create_bitmap()\n");
        return (-2);
    }
    al_set_target_bitmap(bitmap);
    al_clear_to_color(al_map_rgb(255, 255, 255));

    /* max hodnoty X a Y osi */
    int hX = params[3];
    int hY = params[1];

    char NMEA[6];

    int nmeas = 0;
    int lon = 0;
    int lat = 0;
    char c;
    while((c = getchar()) != EOF)
    {
        //printf("%c\n",c);
        if(c==' ') scanf("%[^\n]s",NMEA);
        if(c=='$')
        {
            scanf("%5s",NMEA);
            int tempLat = lat;
            int tempLon = lon;
            short zmena = 0;
            //printf("%s\n",NMEA);

            if (strcmp(NMEA,"GPRMB") == 0 )
            {
                nacitanie(6, &lon, &lat, &nmeas, &zmena);
            }
            else if(strcmp(NMEA,"GPRMC") == 0)
            {
                nacitanie(3, &lon, &lat, &nmeas, &zmena);
            }
            else if(strcmp(NMEA,"GPGGA") == 0)
            {
                nacitanie(2, &lon, &lat, &nmeas, &zmena);
            }

            /* podmienka nacitania najmenej 2 záznamov */
            if (nmeas > 1)
            {
                /* ak sa súradnice nezmenili, nakreslí pixel na daných súradniciach */
                if (lat == tempLat && lon == tempLon && zmena)
                {
                    al_draw_pixel(x-((hX-lon/100)*60-(lon%100)), (hY-lat/100)*60-(lat%100),al_map_rgb(0, 0, 0));
                }
                /* vykreslí čiaru medzi dvoma bodmi */
                else
                {
                    al_draw_line(x-((hX-lon/100)*60-(lon%100)), (hY-lat/100)*60-(lat%100),
                                 x-((hX-tempLon/100)*60-(tempLon%100)),  (hY-tempLat/100)*60-(tempLat%100),
                                 al_map_rgb(0, 0, 0), 1);
                }
            }
            scanf("%[^\n]s",NMEA);
        }
    }

    /* zápis a zničenie bitmapy */
    if(!al_save_bitmap(argv[1], bitmap))
    {
        fprintf(stderr,"Neopravneny alebo zly zapis do suboru\n");
        return (-3);
    }
    al_destroy_bitmap(bitmap);
    return 0;
}
