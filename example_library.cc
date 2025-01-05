#include <stdio.h>
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <fcntl.h>
 
#include "gotcha/gotcha.h"
#include <lustre/lustreapi.h>



typedef int  (*llapi_ladvise_ptr) (int fd, unsigned long long flags,
 int num_advise, struct llapi_lu_ladvise *ladvise);

//int llapi_ladvise(int fd, unsigned long long flags,
// int num_advise, struct llapi_lu_ladvise *ladvise);


typedef int (*open_fptr)(const char *pathname, int flags, mode_t mode);
typedef FILE* (*fopen_fptr)(const char *pathname, const char *mode);

static gotcha_wrappee_handle_t open_handle;
static gotcha_wrappee_handle_t fopen_handle;
static gotcha_wrappee_handle_t llapi_advise_handle;


static int open_wrapper(const char *pathname, int flags, mode_t mode) {
    open_fptr open_wrappee = (open_fptr) gotcha_get_wrappee(open_handle);
    int result = open_wrappee(pathname, flags, mode);
    fprintf(stderr, "open(%s, %d, %u) = %d\n",
            pathname, flags, (unsigned int) mode, result);
    return result;
}

static int llapi_advise_wrapper(int fd, unsigned long long flags,int num_advise, struct llapi_lu_ladvise *ladvise) {
    llapi_ladvise_ptr wrappee = (llapi_ladvise_ptr) gotcha_get_wrappee(llapi_advise_handle);
    int result = wrappee(fd, flags, num_advise,ladvise);
    fprintf(stderr, "llapi_advise(%d, %llu, %d ,_) = %d\n",
            fd, flags, num_advise, result);
    
    return result;
}

static FILE *fopen_wrapper(const char *path, const char *mode) {
  fopen_fptr fopen_wrappee = (fopen_fptr) gotcha_get_wrappee(fopen_handle);
  FILE *result = fopen_wrappee(path, mode);
  fprintf(stderr, "fopen(%s, %s) = %p\n", path, mode, result);
  return result;
 }


static gotcha_binding_t bindings[] = {
  { "open", (void *)open_wrapper, &open_handle },
  { "fopen", (void *)fopen_wrapper, &fopen_handle },
  { "llapi_advise",(void *)llapi_advise_wrapper,&llapi_advise_handle}
    };



class gotcha_setup
{
  public:

    gotcha_setup()
    {
      gotcha_wrap(bindings, 3, "demotool");
    }

};

static gotcha_setup gotcha_demotool;
