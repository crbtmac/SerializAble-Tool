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
        
        //����add_data����������͵���Ҫ  
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
        
        
        //����read_data 
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
        //д���ݵĻ����� 
        std::vector<char>WP;
        
        //�����ݵĻ�����
        char *RP;   
        
        //���л����ݶ����ܴ�С  
        u32 Size;   
        
        //�û�ʵ�ʶ������ݴ�С �������Size������� 
        u32 ReadSize;
        
        //�Ƿ����
        bool BufferOverflow();
        
        //�ж�ϵͳ��С��  ��˷���true С�˷���false
        bool IsBigEndian(); 

};

#define interface class      
interface SerializAble 
{
      virtual void marshal(Seri &seri) = 0;
      virtual void unmarshal(Seri &seri) = 0;
};

#endif
