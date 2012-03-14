#ifndef SERI_H
#define SERI_H

#include <vector>
#include <string>
#include <map>
#include <set>

#define BigtoLittle16(A)            ((((u16)(A) & 0xff00) >> 8) | \
	(((u16)(A) & 0x00ff) << 8))
#define BigtoLittle32(A)          ((((u32)(A) & 0xff000000) >> 24) | \
    (((u32)(A) & 0x00ff0000) >> 8) | \
	(((u32)(A) & 0x0000ff00) << 8) | \
	(((u32)(A) & 0x000000ff) << 24))

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32; 
typedef unsigned long long u64;



class Seri {
    
    public:
        Seri();
        ~Seri();
        
        char* getdata();
        u32 getsize();
        void commit();
        
        //重载add_data满足基本类型的需要  
        void inline add_data(const u8 &d);
        void inline add_data(const u16 &d);
        void inline add_data(const u32 &d);
        void inline add_data(const u64 &d);
        void inline add_data(const float &d);
        void inline add_data(const double &d);
        void inline add_data(const std::string &d);  
        
        //map
        template <typename K, typename V>
        void inline add_data(const std::map<K,V> &hs);
        //set
        template <typename S>
        void inline add_data(const std::set<S> &s);
        //array
        template <typename arr, u32 size>
        void inline add_data(const arr (&a)[size]);
        //vector
        template <typename V>
        void inline add_data(const std::vector<V> &vec);
        
        
        //重载read_data 
        void inline read_data(u8 &d);
        void inline read_data(u16 &d);
        void inline read_data(u32 &d);
        void inline read_data(u64 &d);
        void inline read_data(float &d);
        void inline read_data(double &d);
        void inline read_data(std::string &d);
        
        //map
        template <typename K, typename V>
        void inline read_data(std::map<K, V> &hs);
        
        //set
        template <typename S>
        void inline read_data(std::set<S> &s);
        
        //array
        template <typename arr, u32 size>
        void inline read_data(arr (&a)[size]);
        
        //vector
        template <typename V>
        void inline read_data(std::vector<V> &vec);
       
    private:
        
        bool bigendian;
        //写数据的缓冲区 
        std::vector<char>WP;
        
        //读数据的缓存区
        char *RP;   
        
        //序列化数据对象总大小  
        u32 Size;   
        
        //用户实际读的数据大小 如果超过Size就溢出了 
        u32 ReadSize;
        
        //是否溢出
        bool BufferOverflow();
        
        //判断系统大小端  大端返回true 小端返回false
        bool IsBigEndian(); 

};

#define interface class      
interface SerializAble 
{
      virtual void marshal(Seri &seri) = 0;
      virtual void unmarshal(Seri &seri) = 0;
};

#endif
