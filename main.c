#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <string.h>
#include "gpsbmp.h"

void intToString(int number, int zeros)
{
    int x = 1;
    for (int i = 1; i<zeros; i++) x*=10;
    for (int i = 0; i<zeros; i++){
        printf("%d",number/x);
        number = number%x;
        x/=10;
    }
}

int stringToInt(char * string)
{
    int zaporne = 0;
    int result = 0;
    for(size_t i = 0; i<strlen(string); i++)
    {
        if(string[i] == '-')
        {
            zaporne = 1;
            continue;
        }
        else if(string[i] == '+') continue;
        result*=10;
        result+=(string[i]-'0');
    }
    if(zaporne) return (-1)*result;
    return result;
}

int main (int argc, char * argv[]) {
    if (argc != 6)
    {
        fprintf(stderr,"Nespravny pocet parametrov\n");
        return (-1);
    }

    al_init();
    al_init_image_addon();
    al_init_primitives_addon();

    int params[4];
    for(int i = 2; i<argc; i++) params[i-2] = stringToInt(argv[i]);
    //for(int i = 0; i<4; i++) printf("%d\n",params[i]);
    int x = (params[3]-params[2])*60;
    int y = (params[1]-params[0])*60;
    //printf("X == %d\n",x);
    //printf("Y == %d\n",y);
    ALLEGRO_BITMAP *bitmap = al_create_bitmap(abs(x),abs(y));
    al_set_target_bitmap(bitmap);
    al_clear_to_color(al_map_rgb(255, 255, 255));
    int hX = params[3];
    int hY = params[1];
    char NMEA[7];
    int nmeas = 0;
    int lon = 0;
    int lat = 0;
    while(scanf("%6s",NMEA) != EOF)
    {
        int tempLat = lat;
        int tempLon = lon;
        short zmena = 0;

        if (strcmp(NMEA,"$GPRMB") == 0 )
        {
            char c;
            int counter = 0;
            //printf("$GPRMB\n");
            while(counter<6) if((c=getchar()) == ',') counter++;
            scanf("%d",&lat);
            while((c=getchar()) != 'N' && c != 'S'){}
            if(c == 'S')
            {
                putchar('-');
                intToString(lat/100,2);
                putchar(' ');
                intToString(lat%100,2);
                printf(", ");
                lat*=-1;
            }
            else {
                intToString(lat/100,2);
                putchar(' ');
                intToString(lat%100,2);
                printf(", ");
            }
            getchar();
            scanf("%d",&lon);
            while((c=getchar()) != 'E' && c != 'W'){}
            if(c == 'W')
            {
                putchar('-');
                intToString(lon/100,3);
                putchar(' ');
                intToString(lon%100,2);
                printf("\n");
                lon*=-1;
            }
            else {
                intToString(lon/100,3);
                putchar(' ');
                intToString(lon%100,2);
                printf("\n");
            }
            nmeas++;
            zmena++;
        }
        else if(strcmp(NMEA,"$GPRMC") == 0)
        {
            char c;
            //printf("$GPRMC\n");
            while((c=getchar()) != 'A'){}
            getchar();
            scanf("%d",&lat);
            while((c=getchar()) != 'N' && c != 'S'){}
            if(c == 'S')
            {
                putchar('-');
                intToString(lat/100,2);
                putchar(' ');
                intToString(lat%100,2);
                printf(", ");
                lat*=-1;
            }
            else {
                intToString(lat/100,2);
                putchar(' ');
                intToString(lat%100,2);
                printf(", ");
            }
            getchar();
            scanf("%d",&lon);
            while((c=getchar()) != 'E' && c != 'W'){}
            if(c == 'W')
            {
                putchar('-');
                intToString(lon/100,3);
                putchar(' ');
                intToString(lon%100,2);
                printf("\n");
                lon*=-1;
            }
            else {
                intToString(lon/100,3);
                putchar(' ');
                intToString(lon%100,2);
                printf("\n");
            }
            nmeas++;
            zmena++;
        }
        else if(strcmp(NMEA,"$GPGGA") == 0)
        {
            //printf("$GPGGA\n");
            char c;
            int counter = 0;
            while(counter<2) if((c=getchar()) == ',') counter++;
            scanf("%d",&lat);
            while((c=getchar()) != 'N' && c != 'S'){}
            if(c == 'S')
            {
                putchar('-');
                intToString(lat/100,2);
                putchar(' ');
                intToString(lat%100,2);
                printf(", ");
                lat*=-1;
            }
            else {
                intToString(lat/100,2);
                putchar(' ');
                intToString(lat%100,2);
                printf(", ");
            }
            getchar();
            scanf("%d",&lon);
            while((c=getchar()) != 'E' && c != 'W'){}
            if(c == 'W')
            {
                putchar('-');
                intToString(lon/100,3);
                putchar(' ');
                intToString(lon%100,2);
                printf("\n");
                lon*=-1;
            }
            else {
                intToString(lon/100,3);
                putchar(' ');
                intToString(lon%100,2);
                printf("\n");
            }
            nmeas++;
            zmena++;
        }
        if (nmeas > 1)
        {
            if (lat == tempLat && lon == tempLon && zmena)
            {
                al_draw_pixel(x-((hX-lon/100)*60-(lon%100)), (hY-lat/100)*60-(lat%100),al_map_rgb(0, 0, 0));
            }
            else
            {
                al_draw_line(x-((hX-lon/100)*60-(lon%100)), (hY-lat/100)*60-(lat%100),x-((hX-tempLon/100)*60-(tempLon%100)),  (hY-tempLat/100)*60-(tempLat%100), al_map_rgb(0, 0, 0), 1);
            }
        }
        scanf("%s",NMEA);
    }

    al_save_bitmap(argv[1], bitmap);
    al_destroy_bitmap(bitmap);
    return 0;
}
/* fungujuca
if (nmeas > 1) al_draw_line(x-((hX-lon/100)*60-(lon%100)), (hY-lat/100)*60-(lat%100),x-((hX-tempLon/100)*60-(tempLon%100)),  (hY-tempLat/100)*60-(tempLat%100), al_map_rgb(0, 0, 0), 1);
*/

/*
al_draw_line((hX-tempLon/100)*60-(tempLon%100), (hY-tempLat/100)*60-(tempLat%100), (hX-lon/100)*60-(lon%100),  (hY-lat/100)*60-(lat%100), al_map_rgb(0, 0, 0), 1);
*/
