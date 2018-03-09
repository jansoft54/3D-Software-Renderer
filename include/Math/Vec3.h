#ifndef VEC
#define VEC

struct Vec3
{
    public:
        Vec3(float,float,float);
        virtual ~Vec3() = default;
    public:
        Vec3&   operator*=(float);
        Vec3&   operator+=(const Vec3&);
        Vec3    operator+ (const Vec3&);
        Vec3&   operator-=(const Vec3&);
        Vec3    operator- (const Vec3&);
        bool    equals    (Vec3&);
        static Vec3 crossProduct(const Vec3&,const Vec3&);
        static float dotProduct(const Vec3&,const Vec3&);


    public:
        float z;
        float x;
        float y;

};
#endif // VEC
