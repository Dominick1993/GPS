#ifndef GPSBMP_H
#define GPSBMP_H

/**
 * @brief intToString
 * @param number - number for output
 * @param zeros - length of output number
 */
void intToString(int number, int zeros);

/**
 * @brief stringToInt
 * @param string - string to convert into integer
 * @return converted string
 */
int stringToInt(char * string);

/**
 * @brief vypis
 * @param cislo - number for output
 * @param nuly - length of output number
 * @param neg - negative number tag
 * @param lon - longitude tag
 */
void vypis(int cislo, int nuly, bool neg, bool lon);

/**
 * @brief nacitanie
 * @param commaPosition - determines the number of commas befre longitude
 * @param lon - pointer to longitude variable
 * @param lat - pointer to latitude variable
 * @param nmeas - pointer to number of records parsed
 * @param zmena - pointer to change indicator
 */
void nacitanie(int commaPosition, int* lon, int* lat, int* nmeas, short* zmena);

#endif // GPSBMP_H
