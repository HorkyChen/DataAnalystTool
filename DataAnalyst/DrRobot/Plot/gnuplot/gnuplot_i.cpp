/*-------------------------------------------------------------------------*/
/**
  @file     gnuplot_i.c
  @author   N. Devillard
  @date Sep 1998
  @version  $Revision: 2.10 $
  @brief    C interface to gnuplot.

  gnuplot is a freely available, command-driven graphical display tool for
  Unix. It compiles and works quite well on a number of Unix flavours as
  well as other operating systems. The following module enables sending
  display requests to gnuplot through simple C calls.

*/
/*--------------------------------------------------------------------------*/

/*
    $Id: gnuplot_i.c,v 2.10 2003/01/27 08:58:04 ndevilla Exp $
    $Author: ndevilla $
    $Date: 2003/01/27 08:58:04 $
    $Revision: 2.10 $
    $Revised by Horky@2014/09/05
 */

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "gnuplot_i.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include <string>

#if (defined(WIN32)||defined(_WIN32))
#include <io.h>
#include <stdio.h>
#define popen(cmd, type) _popen(cmd,type)
#define pclose(cmd) _pclose(cmd)
#else
#include <unistd.h>
#endif // #ifdef WIN32 _WIN32

#ifdef __cplusplus
extern "C" {
#endif
/*---------------------------------------------------------------------------
                                Defines
 ---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                          Prototype Functions
 ---------------------------------------------------------------------------*/

/**
 * Creates a temporary file name for writing
 *
 * @author Peter (12/9/2011)
 *
 * @param handle
 *
 * @return char const * Pointer to file name string.
 */
char const * gnuplot_tmpfile(gnuplot_ctrl * handle);

/**
 * Plot a temporary file.
 *
 * @author Peter (12/9/2011)
 *
 * @param handle
 * @param tmp_filename
 * @param title
 * @param hasXticLabel
 */
void gnuplot_plot_atmpfile(gnuplot_ctrl * handle, char const* tmp_filename, char const* title, bool hasXticLabel);

/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/**
  @brief    Opens up a gnuplot session, ready to receive commands.
  @return   Newly allocated gnuplot control structure.

  This opens up a new gnuplot session, ready for input. The struct
  controlling a gnuplot session should remain opaque and only be
  accessed through the provided functions.

  The session must be closed using gnuplot_close().
 */
/*--------------------------------------------------------------------------*/

gnuplot_ctrl * gnuplot_init(void)
{
    gnuplot_ctrl *  handle ;
    int i;

#if (!defined(WIN32)||!defined(_WIN32))
    if (getenv("DISPLAY") == NULL) {
        fprintf(stderr, "cannot find DISPLAY variable: is it set?\n") ;
    }
#endif // #ifndef WIN32  _WIN32


    /*
     * Structure initialization:
     */
    handle = (gnuplot_ctrl*)malloc(sizeof(gnuplot_ctrl)) ;
    handle->nplots = 0 ;
    gnuplot_setstyle(handle, "points") ;
    handle->ntmp = 0 ;
    memset(handle->commandFile,sizeof(handle->commandFile),0);
    memset(handle->outputFile,sizeof(handle->outputFile),0);
    handle->outputFile[0] = 0;

    handle->gnucmd = popen(gnuplot_path, "w") ;
    if (handle->gnucmd == NULL) {
        fprintf(stderr, "error starting gnuplot, is gnuplot or gnuplot.exe in your path?\n") ;
        free(handle) ;
        return NULL ;
    }

    for (i=0;i<GP_MAX_TMP_FILES; i++)
    {
        handle->tmp_filename_tbl[i] = NULL;
    }
    
    return handle;
}


/*-------------------------------------------------------------------------*/
/**
  @brief    Closes a gnuplot session previously opened by gnuplot_init()
  @param    handle Gnuplot session control handle.
  @return   void

  Kills the child PID and deletes all opened temporary files.
  It is mandatory to call this function to close the handle, otherwise
  temporary files are not cleaned and child process might survive.

 */
/*--------------------------------------------------------------------------*/

void gnuplot_close(gnuplot_ctrl * handle,short closePlot)
{
    int     i ;

    if (closePlot && pclose(handle->gnucmd) == -1) {
        fprintf(stderr, "problem closing communication to gnuplot\n") ;
        return ;
    }
    if (handle->ntmp) {
        for (i=0 ; i<handle->ntmp ; i++) {
            remove(handle->tmp_filename_tbl[i]) ;
            free(handle->tmp_filename_tbl[i]);
            handle->tmp_filename_tbl[i] = NULL;

        }
    }
    free(handle) ;
    return ;
}


/*-------------------------------------------------------------------------*/
/**
  @brief    Sends a command to an active gnuplot session.
  @param    handle Gnuplot session control handle
  @param    cmd    Command to send, same as a printf statement.

  This sends a string to an active gnuplot session, to be executed.
  There is strictly no way to know if the command has been
  successfully executed or not.
  The command syntax is the same as printf.

  Examples:

  @code
  gnuplot_cmd(g, "plot %d*x", 23.0);
  gnuplot_cmd(g, "plot %.18e * cos(%.18e * x)", 32.0, -3.0);
  @endcode

  Since the communication to the gnuplot process is run through
  a standard Unix pipe, it is only unidirectional. This means that
  it is not possible for this interface to query an error status
  back from gnuplot.
 */
/*--------------------------------------------------------------------------*/

void gnuplot_cmd(gnuplot_ctrl *  handle, char const *  cmd, ...)
{
    if(!cmd)
    {
        return;
    }
    
    va_list ap ;

    va_start(ap, cmd);
    vfprintf(handle->gnucmd, cmd, ap);
    va_end(ap);

    fputs("\n", handle->gnucmd) ;
    fflush(handle->gnucmd);
    
    return ;
}


/*-------------------------------------------------------------------------*/
/**
  @brief    Change the plotting style of a gnuplot session.
  @param    h Gnuplot session control handle
  @param    plot_style Plotting-style to use (character string)
  @return   void

  The provided plotting style is a character string. It must be one of
  the following:

  - lines
  - points
  - linespoints
  - impulses
  - dots
  - steps
  - errorbars
  - boxes
  - boxeserrorbars
 */
/*--------------------------------------------------------------------------*/

void gnuplot_setstyle(gnuplot_ctrl * h, const char * plot_style)
{
    if (strcmp(plot_style, "lines") &&
        strcmp(plot_style, "points") &&
        strcmp(plot_style, "linespoints") &&
        strcmp(plot_style, "impulses") &&
        strcmp(plot_style, "dots") &&
        strcmp(plot_style, "steps") &&
        strcmp(plot_style, "errorbars") &&
        strcmp(plot_style, "boxes") &&
        strcmp(plot_style, "boxerrorbars")) {
        fprintf(stderr, "warning: unknown requested style: using points\n") ;
        strcpy(h->pstyle, "points") ;
    } else {
        strcpy(h->pstyle, plot_style) ;
    }
    
    h->commandFile[0] = 0;
    
    return ;
}

/*-------------------------------------------------------------------------*/
/**
 @brief    Sets the command file instead of plot/replot command.
 @param    commandFile The GNU Plot command file in full path.
 @return   void
 
 Sets the command file instead of plot/replot command.
 */
/*--------------------------------------------------------------------------*/
void gnuplot_set_commandFile(gnuplot_ctrl * h, const char * commandFile)
{
    if(h){
        strcpy(h->commandFile , commandFile);
    }
}
    
    
/*-------------------------------------------------------------------------*/
/**
 @brief    Sets the output file for exporting.
 @param    outputFile The target file in full path.
 @return   void
 
 Sets the command file instead of plot/replot command.
 */
/*--------------------------------------------------------------------------*/
void gnuplot_set_outputFile(gnuplot_ctrl * h, const char * outputFile)
{
    if(h){
        strcpy(h->outputFile , outputFile);
    }
}

/*-------------------------------------------------------------------------*/
/**
  @brief    Sets the x label of a gnuplot session.
  @param    h Gnuplot session control handle.
  @param    label Character string to use for X label.
  @return   void

  Sets the x label for a gnuplot session.
 */
/*--------------------------------------------------------------------------*/

void gnuplot_set_xlabel(gnuplot_ctrl * h, const char * label)
{
    gnuplot_cmd(h, "set xlabel \"%s\"", label) ;
}


/*-------------------------------------------------------------------------*/
/**
  @brief    Sets the y label of a gnuplot session.
  @param    h Gnuplot session control handle.
  @param    label Character string to use for Y label.
  @return   void

  Sets the y label for a gnuplot session.
 */
/*--------------------------------------------------------------------------*/

void gnuplot_set_ylabel(gnuplot_ctrl * h, char * label)
{
    gnuplot_cmd(h, "set ylabel \"%s\"", label) ;
}


/*-------------------------------------------------------------------------*/
/**
  @brief    Resets a gnuplot session (next plot will erase previous ones).
  @param    h Gnuplot session control handle.
  @return   void

  Resets a gnuplot session, i.e. the next plot will erase all previous
  ones.
 */
/*--------------------------------------------------------------------------*/

void gnuplot_resetplot(gnuplot_ctrl * h)
{
    int     i ;
    if (h->ntmp) {
        for (i=0 ; i<h->ntmp ; i++) {
            remove(h->tmp_filename_tbl[i]) ;
            free(h->tmp_filename_tbl[i]);
            h->tmp_filename_tbl[i] = NULL;

        }
    }
    h->ntmp = 0 ;
    h->nplots = 0 ;
    return ;
}

/*-------------------------------------------------------------------------*/
/**
  @brief    Plots a 2d graph from a list of floats.
  @param    handle  Gnuplot session control handle.
  @param    d       Array of floats.
  @param    n       Number of values in the passed array.
  @param    title   Title of the plot.
  @return   void

  Plots out a 2d graph from a list of floats. The x-coordinate is the
  index of the float in the list, the y coordinate is the float in
  the list.

  Example:

  @code
    gnuplot_ctrl    *h ;
    float          d[50] ;
    int             i ;

    h = gnuplot_init() ;
    for (i=0 ; i<50 ; i++) {
        d[i] = (float)(i*i) ;
    }
    gnuplot_plot_x(h, d, 50, "parabola") ;
    sleep(2) ;
    gnuplot_close(h) ;
  @endcode
 */
/*--------------------------------------------------------------------------*/

void gnuplot_plot_x(
    gnuplot_ctrl    *   handle,
    float          *   d,
    std::string         *   label,
    int                 n,
    const char            *   title
)
{
    int     i ;
    FILE*   tmpfd ;
    char const * tmpfname;

    if (handle==NULL || d==NULL || (n<1)) return ;

    /* Open temporary file for output   */
    tmpfname = gnuplot_tmpfile(handle);
    tmpfd = fopen(tmpfname, "w");

    if (tmpfd == NULL) {
        fprintf(stderr,"cannot create temporary file: exiting plot") ;
        return ;
    }

    /* Write data to this file  */
    for (i=0 ; i<n ; i++) {
        if(label){
            fprintf(tmpfd, "%.5e %s\n", d[i],(label+i)->c_str());
        }
        else {
            fprintf(tmpfd, "%.5e\n", d[i]);
        }
    }
    fclose(tmpfd) ;

    gnuplot_plot_atmpfile(handle,tmpfname,title,label!=NULL);
    return ;
}


void gnuplot_plot_x_int(
    gnuplot_ctrl    *   handle,
    int          *   d,
    std::string         *   label,
    int                 n,
    const char            *   title
)
{
    int     i ;
    FILE*   tmpfd ;
    char const * tmpfname;

    if (handle==NULL || d==NULL || (n<1)) return ;

    /* Open temporary file for output   */
    tmpfname = gnuplot_tmpfile(handle);
    tmpfd = fopen(tmpfname, "w");

    if (tmpfd == NULL) {
        fprintf(stderr,"cannot create temporary file: exiting plot") ;
        return ;
    }

    /* Write data to this file  */
    for (i=0 ; i<n ; i++) {
        if(label){
          fprintf(tmpfd, "%d %s\n", d[i],(label+i)->c_str());
        }
        else {
          fprintf(tmpfd, "%d\n", d[i]);
        }
    }
    fclose(tmpfd) ;

    gnuplot_plot_atmpfile(handle,tmpfname,title,label!=NULL);
    return ;
}


/*-------------------------------------------------------------------------*/
/**
  @brief    Plot a 2d graph from a list of points.
  @param    handle      Gnuplot session control handle.
  @param    x           Pointer to a list of x coordinates.
  @param    y           Pointer to a list of y coordinates.
  @param    n           Number of floats in x (assumed the same as in y).
  @param    title       Title of the plot.
  @return   void

  Plots out a 2d graph from a list of points. Provide points through a list
  of x and a list of y coordinates. Both provided arrays are assumed to
  contain the same number of values.

  @code
    gnuplot_ctrl    *h ;
    float          x[50] ;
    float          y[50] ;
    int             i ;

    h = gnuplot_init() ;
    for (i=0 ; i<50 ; i++) {
        x[i] = (float)(i)/10.0 ;
        y[i] = x[i] * x[i] ;
    }
    gnuplot_plot_xy(h, x, y, 50, "parabola") ;
    sleep(2) ;
    gnuplot_close(h) ;
  @endcode
 */
/*--------------------------------------------------------------------------*/

void gnuplot_plot_xy(
    gnuplot_ctrl    *   handle,
    float          *   x,
    float          *   y,
    int                 n,
    char            *   title
)
{
    int     i ;
    FILE*   tmpfd ;
    char const * tmpfname;

    if (handle==NULL || x==NULL || y==NULL || (n<1)) return ;

    /* Open temporary file for output   */
    tmpfname = gnuplot_tmpfile(handle);
    tmpfd = fopen(tmpfname, "w");

    if (tmpfd == NULL) {
        fprintf(stderr,"cannot create temporary file: exiting plot") ;
        return ;
    }

    /* Write data to this file  */
    for (i=0 ; i<n; i++) {
        fprintf(tmpfd, "%.18e %.18e\n", x[i], y[i]) ;
    }
    fclose(tmpfd) ;

    gnuplot_plot_atmpfile(handle,tmpfname,title,false);
    return ;
}



/*-------------------------------------------------------------------------*/
/**
  @brief    Open a new session, plot a signal, close the session.
  @param    title   Plot title
  @param    style   Plot style
  @param    label_x Label for X
  @param    label_y Label for Y
  @param    x       Array of X coordinates
  @param    y       Array of Y coordinates (can be NULL)
  @param    n       Number of values in x and y.
  @return

  This function opens a new gnuplot session, plots the provided
  signal as an X or XY signal depending on a provided y, waits for
  a carriage return on stdin and closes the session.

  It is Ok to provide an empty title, empty style, or empty labels for
  X and Y. Defaults are provided in this case.
 */
/*--------------------------------------------------------------------------*/

void gnuplot_plot_once(
  char    *   title,
  char    *   style,
  char    *   label_x,
  char    *   label_y,
  float  *   x,
  float  *   y,
  int         n
)
{
  gnuplot_ctrl    *   handle ;

  if (x==NULL || n<1) return ;

  if ((handle = gnuplot_init()) == NULL) return ;
  if (style!=NULL) {
      gnuplot_setstyle(handle, style);
  } else {
      gnuplot_setstyle(handle, "lines");
  }
  if (label_x!=NULL) {
      gnuplot_set_xlabel(handle, label_x);
  } else {
      gnuplot_set_xlabel(handle, "X");
  }
  if (label_y!=NULL) {
      gnuplot_set_ylabel(handle, label_y);
  } else {
      gnuplot_set_ylabel(handle, "Y");
  }
  if (y==NULL) {
      gnuplot_plot_x(handle, x, NULL, n, title);
  } else {
      gnuplot_plot_xy(handle, x, y, n, title);
  }
  printf("press ENTER to continue\n");
  while (getchar()!='\n') {}
  gnuplot_close(handle,true);
  return ;
}

void gnuplot_plot_slope(
    gnuplot_ctrl    *   handle,
    float              a,
    float              b,
    const char            *   title
)
{
    char const *    cmd    = (handle->nplots > 0) ? "replot" : "plot";
    title                  = (title == NULL)      ? "(none)" : title;

    gnuplot_cmd(handle, "%s %.18e * x + %.18e title \"%s\" with %s",
                  cmd, a, b, title, handle->pstyle) ;

    handle->nplots++ ;
    return ;
}


void gnuplot_plot_equation(
    gnuplot_ctrl    *   h,
    char            *   equation,
    const char            *   title
)
{
    char const *    cmd    = (h->nplots > 0) ? "replot" : "plot";
    title                  = (title == NULL)      ? "(none)" : title;

    gnuplot_cmd(h, "%s %s title \"%s\" with %s",
                  cmd, equation, title, h->pstyle) ;
    h->nplots++ ;
    return ;
}


int gnuplot_write_x_csv(
    char const * fileName,
    float const * d,
    int n,
    char const * title)
{
    int     i;
    FILE*   fileHandle;

    if (fileName==NULL || d==NULL || (n<1))
    {
        return -1;
    }

    fileHandle = fopen(fileName, "w");

    if (fileHandle == NULL)
    {
        return -1;
    }

    // Write Comment.
    if (title != NULL)
    {
        fprintf(fileHandle, "# %s\n", title) ;
    }

    /* Write data to this file  */
    for (i=0 ; i<n; i++)
    {
        fprintf(fileHandle, "%d, %.18e\n", i, d[i]) ;
    }

    fclose(fileHandle) ;

    return 0;
}

int gnuplot_write_xy_csv(
    char const *        fileName,
    float const    *   x,
    float const    *   y,
    int                 n,
    char const      *   title)
{
    int     i ;
    FILE*   fileHandle;

    if (fileName==NULL || x==NULL || y==NULL || (n<1))
    {
        return -1;
    }

    fileHandle = fopen(fileName, "w");

    if (fileHandle == NULL)
    {
        return -1;
    }

    // Write Comment.
    if (title != NULL)
    {
        fprintf(fileHandle, "# %s\n", title) ;
    }

    /* Write data to this file  */
    for (i=0 ; i<n; i++)
    {
        fprintf(fileHandle, "%.18e, %.18e\n", x[i], y[i]) ;
    }

    fclose(fileHandle) ;

    return 0;
}

int gnuplot_write_multi_csv(
    char const *        fileName,
    float const    **  xListPtr,
    int                 n,
    int                 numColumns,
    char const      *   title)
{
    int     i;
    int     j;
    FILE*   fileHandle;

    if (fileName==NULL || xListPtr==NULL || (n<1) || numColumns <1)
    {
        return -1;
    }

    for (j=0;j<numColumns;j++)
    {
        if (xListPtr[j] == NULL)
        {
            return -1;
        }
    }

    fileHandle = fopen(fileName, "w");

    if (fileHandle == NULL)
    {
        return -1;
    }

    // Write Comment.
    if (title != NULL)
    {
        fprintf(fileHandle, "# %s\n", title) ;
    }

    /* Write data to this file  */
    for (i=0 ; i<n; i++)
    {
        fprintf(fileHandle, "%d, %.18e", i, xListPtr[0][i]) ;
        for (j=1;j<numColumns;j++)
        {
            fprintf(fileHandle, ", %.18e", xListPtr[j][i]) ;
        }
        fprintf(fileHandle, "\n");
    }

    fclose(fileHandle) ;

    return 0;
}

char const * gnuplot_tmpfile(gnuplot_ctrl * handle)
{
    static char const * tmp_filename_template = "gnuplot_tmpdatafile_XXXXXX";
    char *              tmp_filename = NULL;
    int                 tmp_filelen = strlen(tmp_filename_template);

#if (!defined(WIN32)||!defined(_WIN32))
    int                 unx_fd;
#endif // #ifndef WIN32 _WIN32

    assert(handle->tmp_filename_tbl[handle->ntmp] == NULL);

    /* Open one more temporary file? */
    if (handle->ntmp == GP_MAX_TMP_FILES - 1) {
        fprintf(stderr,
                "maximum # of temporary files reached (%d): cannot open more",
                GP_MAX_TMP_FILES) ;
        return NULL;
    }

    tmp_filename = (char*) malloc(tmp_filelen+1);
    if (tmp_filename == NULL)
    {
        return NULL;
    }
    strcpy(tmp_filename, tmp_filename_template);

#if (defined(WIN32)||defined(_WIN32))
    if (_mktemp(tmp_filename) == NULL)
    {
        return NULL;
    }
#else // #ifdef WIN32  _WIN32
    unx_fd = mkstemp(tmp_filename);
    if (unx_fd == -1)
    {
        return NULL;
    }
    close(unx_fd);

#endif // #ifdef WIN32 _WIN32

    handle->tmp_filename_tbl[handle->ntmp] = tmp_filename;
    handle->ntmp ++;
    return tmp_filename;
}

void gnuplot_set_terminal_as_needed(gnuplot_ctrl * handle)
{
    if(strlen(handle->outputFile)>0)
    {
        gnuplot_cmd(handle,"set terminal svg size 640,480");
        gnuplot_cmd(handle,"set output \"%s\"",handle->outputFile);
    }
}
    
void gnuplot_reset_terminal_as_needed(gnuplot_ctrl * handle)
{
    if(strlen(handle->outputFile)>0)
    {
        gnuplot_cmd(handle,"set terminal x11");
        gnuplot_cmd(handle,"set output");
        handle->outputFile[0] = 0;
    }
}
    
void gnuplot_plot_atmpfile(gnuplot_ctrl * handle, char const* tmp_filename, char const* title, bool hasXticLabel)
{
    char const *    cmd    = (handle->nplots > 0) ? "replot" : "plot";
    title                  = (title == NULL)      ? "(none)" : title;
    
    gnuplot_set_terminal_as_needed(handle);
    
    if(strlen(handle->commandFile)>0)
    {
        gnuplot_cmd(handle,"call \"%s\" \"%s\" \"%s\"",handle->commandFile,tmp_filename,title);
        handle->commandFile[0] = 0;
    }
    else if(hasXticLabel)
    {
        gnuplot_cmd(handle, "%s \"%s\" using 1:xticlabels(2) title \"%s\" with %s", cmd, tmp_filename,
                    title, handle->pstyle) ;
    }
    else
    {
        gnuplot_cmd(handle, "%s \"%s\" title \"%s\" with %s", cmd, tmp_filename,
                    title, handle->pstyle) ;
    }
    
    handle->nplots++ ;
    
    gnuplot_reset_terminal_as_needed(handle);
}

#ifdef __cplusplus
}
#endif

/* vim: set ts=4 et sw=4 tw=75 */
