#ifndef __OBJECT__
#define __OBJECT__

class Object {
  private :
    int _d; // the dimension
    int * _val; // values of the object

  public :
    // static function for calculating this euclidean distance of two object
    static double distance(Object & a, Object & b);

    // public function for setting a certain dimension value
    void setVal(int d, int val);

    // public function for getting a certain dimension value
    int getVal(int d);

    Object(int d);
    ~Object();
};

#endif
