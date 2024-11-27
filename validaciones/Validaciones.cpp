/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Bryan Alexander Rosero Delgado
 * FECHA CREACION: Jueves,  21 de noviembre de 2024
 * FECHA MODIFICACION: Jueves,  21 de noviembre de 2024
 * Nivel: TERCERO     NRC: 1992
 *************************/

#include "Validaciones.hpp"
#include <conio.h>

int Validaciones::leerInt()
{
    const int INT_TAM = 12;
    char ingreso[INT_TAM] = "";
    char c;

    int pos = 0;
    do
    {
        c = getch();
        if (pos != INT_TAM - 1)
        {
            if (('0' <= c && c <= '9') || (c == '-' && pos == 0))
            {
                putchar(c); //
                ingreso[pos] = c;
                ingreso[++pos] = '\0';
            }
        }

        if ((c == '\b' || c == 127) && pos != 0) {
            putchar('\b');
            putchar(' ');
            putchar('\b');
            ingreso[--pos] = '\0';
        }
    } while ((c != '\n' && c != '\r') || pos == 0);

    putchar('\n');
    return atoi(ingreso);
}

float Validaciones::leerFloat()
{
    const int FLOAT_TAM = 42;
    char ingreso[FLOAT_TAM] = "";
    char c;
    bool tienePunto;

    int pos = 0;
    do
    {
        c = getch();
        if (pos != FLOAT_TAM - 1)
        {
            if (('0' <= c && c <= '9') || (c == '-' && pos == 0))
            {
                putchar(c); //
                ingreso[pos] = c;
                ingreso[++pos] = '\0';
            }

            if (!tienePunto && (c == '.' || c == ',')) {
                c = '.';
                putchar(c); // 1
                ingreso[pos] = c;
                ingreso[++pos] = '\0';

                tienePunto = true;
            }
        }

        if ((c == '\b' || c == 127) && pos != 0) {
            putchar('\b');
            putchar(' ');
            putchar('\b');

            if (ingreso[--pos] == '.')
                tienePunto = false;
            ingreso[pos] = '\0';
        }
    } while ((c != '\n' && c != '\r') || pos == 0);

    putchar('\n');
    return atof(ingreso);
}

double Validaciones::leerDouble()
{
    const int DOUBLE_TAM = 42;
    char ingreso[DOUBLE_TAM] = "";
    char c;
    bool tienePunto;

    int pos = 0;
    do
    {
        c = getch();
        if (pos != DOUBLE_TAM - 1)
        {
            if (('0' <= c && c <= '9') || (c == '-' && pos == 0))
            {
                putchar(c); //
                ingreso[pos] = c;
                ingreso[++pos] = '\0';
            }

            if (!tienePunto && (c == '.' || c == ',')) {
                c = '.';
                putchar(c); // 1
                ingreso[pos] = c;
                ingreso[++pos] = '\0';

                tienePunto = true;
            }
        }

        if ((c == '\b' || c == 127) && pos != 0) {
            putchar('\b');
            putchar(' ');
            putchar('\b');

            if (ingreso[--pos] == '.')
                tienePunto = false;
            ingreso[pos] = '\0';
        }
    } while ((c != '\n' && c != '\r') || pos == 0);

    putchar('\n');
    return atof(ingreso);
}

char Validaciones::leerLetra()
{
    char c;

    do
    {
        c = getch();

        if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'))
        {
            putchar(c);
        }

        if ((c == '\b' || c == 127)) {
            putchar('\b');
            putchar(' ');
            putchar('\b');
            c = ' ';

        }
    } while ((c != '\n' && c != '\r') || c == ' ');

    return c;
}

std::string Validaciones::leerPalabra()
{
    char c;
    std::string saveStr = "";

    do
    {
        c = getch();

        if ('A' <= c && c <= 'Z' || 'a' <= c && c <= 'z')
        {
            putchar(c); // 1
            saveStr.push_back(c);
        }

        if ((c == '\b' || c == 127) && !saveStr.empty()) {
            putchar('\b');
            putchar(' ');
            putchar('\b');
            saveStr.pop_back();
        }

    } while ((c != '\n' && c != '\r') || saveStr.empty()); // 2

    return saveStr;
}
