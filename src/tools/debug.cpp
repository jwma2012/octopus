/*** Debug source. ***/

/** Version 1 + Functional Model Modification **/

/** Included files. **/
#include "debug.hpp"

/** Implemented functions. **/
/* Print debug title string.
   @param   str     String of debug title. */
void Debug::debugTitle(const char *str)
{
    if (TITLE == true)                  /* If debug option is set. */
        printf("\033[0;45;1m%s\033[0m\n", str); /* Print debug title string. */
        /* "\033[字背景颜色;字体颜色m字符串\033[0m" 用作输出颜色控制*/
}

/* Print debug item string. Can be used in a formatted style like a printf().
   @param   format  Format of debug item. Same as printf().
                    POTENTIALPROBLEM: the length of format can not exceed MAX_FORMAT_LEN - 1, but there is no check.
   @param   ...     Other argument variables to print. Same as printf(). */
void Debug::debugItem(const char *format, ...)
{
    char newFormat[MAX_FORMAT_LEN];

    va_list args;
    va_start(args, format);             /* Start of variable arguments. */

    if (DEBUG == true)                  /* If debug option is set. */
    {
        sprintf(newFormat, "\033[0;42;1m%s\033[0m\n", format); /* Wrap format in a style. */
        vprintf(newFormat, args);       /* Print string of debug item. */
    }

    va_end(args);                       /* End of variable arguments. */
}
void Debug::debugCur(const char *format, ...)
{
    char newFormat[MAX_FORMAT_LEN];

    va_list args;
    va_start(args, format);             /* Start of variable arguments. */

    if (CUR == true)                  /* If debug option is set. */
    {
        sprintf(newFormat, "%s\n", format); /* Wrap format in a style. */
        vprintf(newFormat, args);       /* Print string of debug item. */
    }

    va_end(args);                       /* End of variable arguments. */
}
/* Print necessary information at start period. Can be used in a formatted style like a printf().
   @param   format  Format of debug item. Same as printf().
                    POTENTIALPROBLEM: the length of format can not exceed MAX_FORMAT_LEN - 1, but there is no check.
   @param   ...     Other argument variables to print. Same as printf(). */
void Debug::notifyInfo(const char *format, ...)
{
    char newFormat[MAX_FORMAT_LEN];

    va_list args;
    va_start(args, format);             /* Start of variable arguments. */
    sprintf(newFormat, "\033[4m%s\033[0m\n", format); /* Wrap format in a style. */
    vprintf(newFormat, args);           /* Print string of notify information. */
    va_end(args);                       /* End of variable arguments. */
}

/* Print error information at start period. Can be used in a formatted style like a printf().
   @param   format  Format of debug item. Same as printf().
                    POTENTIALPROBLEM: the length of format can not exceed MAX_FORMAT_LEN - 1, but there is no check.
   @param   ...     Other argument variables to print. Same as printf(). */
void Debug::notifyError(const char *format, ...)
{
    char newFormat[MAX_FORMAT_LEN];

    va_list args;
    va_start(args, format);             /* Start of variable arguments. */
    sprintf(newFormat, "\033[0;31m%s\033[0m\n", format); /* Wrap format in a style. */
    vprintf(newFormat, args);           /* Print string of notify information. */
    va_end(args);                       /* End of variable arguments. */
}

/* Start timer and display information. */
void Debug::startTimer(const char *timerName)
{
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv,&tz);              /* Get start time. */
    if (TIMER == true) {                /* If debug option is set. */
        printf("%s is started.\n", timerName);
        Debug::startTime = tv.tv_sec * 1000 * 1000 + tv.tv_usec; /* Convert to milliseconds and save. */
    //microseconds
    }
}

/* End timer and display information. */
void Debug::endTimer(const char *timerName)
{
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv,&tz);              /* Get end time. */
    long endTime;
    if (TIMER == true) {                /* If debug option is set. */
        endTime = tv.tv_sec * 1000 * 1000 + tv.tv_usec; /* Convert to milliseconds. */
    //microseconds
        printf("%s is ended. Cost %ld us.\n", timerName, (endTime - Debug::startTime));
    }
}

uint64_t Debug::NowMicros() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return static_cast<uint64_t>(tv.tv_sec) * 1000 * 1000 + tv.tv_usec;
}


/** Variables. **/
long Debug::startTime;                  /* Last start time in milliseconds. */