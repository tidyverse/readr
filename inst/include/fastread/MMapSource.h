#ifndef FASTREAD_MMapSource_H
#define FASTREAD_MMapSource_H

namespace fastread {

    template <
        typename LinePolicy = KeepAllLines,
        typename SeparatorPolicy = SingleCharacterSeparator
    >
    class MMapSource : public Source< MMapSource<LinePolicy, SeparatorPolicy>, LinePolicy, SeparatorPolicy>{
    public:
        typedef Source<MMapSource, LinePolicy, SeparatorPolicy> Base ;

        MMapSource( const std::string& filename, LinePolicy line_policy_ = LinePolicy(), SeparatorPolicy sep_policy_ = SeparatorPolicy() ) :
            Base(line_policy_, sep_policy_)
        {
            using namespace boost::interprocess;

            try {
              file_mapping fm(filename.c_str(), read_only);
              mr = new mapped_region(fm, read_only);
            }

            catch(interprocess_exception& e){
              stop( "cannot read file information" ) ;
            }
            filesize = mr->get_size();
            memory_start = static_cast<char*>(mr->get_address());

            eof = memory_start + filesize ;
            Base::set(memory_start, eof);

            last_full_line = eof - 1 ;
            while( *last_full_line != '\n' ) --last_full_line;

        }

        ~MMapSource(){
          delete(mr);
        }


        inline bool more(){ return false ;}

        inline bool ensure_full_line(){
            return Base::p < last_full_line ;
        }

        inline bool can_seek(){
            return true ;
        }

        inline void seek( int pos ){
            Base::p = memory_start + pos ;
        }

        inline double byte_offset(){
            return Base::p - memory_start ;
        }

    private:
        size_t filesize ;
        char* memory_start ;
        char* eof ;
        char* last_full_line ;
        boost::interprocess::mapped_region* mr;
    } ;
}

#endif
