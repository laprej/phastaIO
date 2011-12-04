/*  Primary interface for the Phasta Binary read and write routines these*/
/*  functions are 'C' callable.( All arguments have been kept as pointers to*/
/*  facilitate calling from Fortran )*/
/*  Anil Kumar Karanam  Spring 2003*/
#ifndef _PHASTAIO_H_
#define _PHASTAIO_H_


#ifdef WIN32
#define queryphmpiio_ QUERYPHMPIIO
#define initphmpiio_ INITPHMPIIO
#define finalizephmpiio_ FINALIZEPHMPIIO
#define openfile_ OPENFILE
#define closefile_ CLOSEFILE
#define readheader_ READHEADER
#define readdatablock_ READDATABLOCK
#define writeheader_ WRITEHEADER
#define writedatablock_ WRITEDATABLOCK
#define writestring_ WRITESTRING
#define togglestrictmode_ TOGGLESTRICTMODE
#define SwapArrayByteOrder_ SWAPARRAYBYTEORDER
#define isLittleEndian_ ISLITTLEENDIAN
#ifdef intel
#define ios_base ios
#endif
#elif ( defined IBM )
#define queryphmpiio_ queryphmpiio
#define initphmpiio_ initphmpiio
#define finalizephmpiio_ finalizephmpiio
#define openfile_ openfile
#define closefile_ closefile
#define readheader_ readheader
#define readdatablock_ readdatablock
#define writeheader_ writeheader
#define writedatablock_ writedatablock
#define writestring_ writestring
#define togglestrictmode_ togglestrictmode
#endif


#if defined (__cplusplus)
extern "C" {
#endif

  void mem_alloc( void* p, char* type, int size );

  void
  queryphmpiio_( const char filename[],
		 int *nfields,
		 int *nppf );

  int
  initphmpiio_( int *nfields,
		int *nppf,
		int *nfiles,
		int *filehandle,
		const char mode[] );

  void
  finalizephmpiio_( int *fileDescriptor );

    void
    SwapArrayByteOrder_( void* array,
                         int   nbytes,
                         int   nItems ) ;
    void

    openfile_( const char filename[],
               const char mode[],
               int* fileDescriptor );

    void
    closefile_( int* fileDescriptor,
                const char mode[] );

    void
    readheader_( int*   fileDescriptor,
                 const char  keyphrase[],
                 void*  valueArray,
                 int*   nItems,
                 const char   datatype[],
                 const char   iotype[] );

    void
    writeheader_( const int*  fileDescriptor,
                  const char keyphrase[],
                  const void* valueArray,
                  const int*  nItems,
                  const int*  ndataItems,
                  const char  datatype[],
                  const char  iotype[] );

    void
    readdatablock_( int*  fileDescriptor,
                    const char keyphrase[],
                    void* valueArray,
                    int*  nItems,
                    const char  datatype[],
                    const char  iotype[] );


    void
    writedatablock_( const int*   fileDescriptor,
                     const char  keyphrase[],
                     const void*  valueArray,
                     const int*   nItems,
                     const char   datatype[],
                     const char   iotype[]  );

    void
    writestring_( int* fileDescriptor,
                  const char inString[] );

    void
    togglestrictmode_( );

  int
  isLittleEndian_( ) ;

#ifdef __cplusplus
} // end of extern "C".

#include <string>

namespace PHASTA {
template<class T>
struct PhastaIO_traits;

template<>
struct PhastaIO_traits<int> {
  static const char* const type_string;
};


template<>
struct PhastaIO_traits<double> {
  static const char* const type_string;
};


template<class T>
void
write_data_block( const int   fileDescriptor,
		  const std::string keyphrase,
		  const T* const  valueArray,
		  const int   nItems,
		  const bool inBinary = false) {
  writedatablock_(&fileDescriptor,
		  keyphrase.c_str(),
		  reinterpret_cast<const void*>(valueArray),
		  &nItems,
		  PhastaIO_traits<T>::type_string,
		  inBinary ? "binary" : "text");

}
template<class T>
void
write_header( const int  fileDescriptor,
		 const std::string& keyphrase,
		 const T* valueArray,
		 const int  nItems,
		 const int  nDataItems,
		 const bool inBinary = false) {
      writeheader_(&fileDescriptor,
		   keyphrase.c_str(),
		   reinterpret_cast<const void*>(valueArray),
		   &nItems,
		   &nDataItems,
		   PhastaIO_traits<T>::type_string,
		   inBinary ? "binary" : "text");
}


} // namespace PHASTA

#endif // __cplusplus

#endif // _PHASTAIO_H_
