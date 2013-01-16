#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <cmath>
#include <limits>
#include <vector>
using namespace std;

struct point {
    float x;
    float y;
};

struct triangle {
    float ax;
    float ay;
    float bx;
    float by;
    float cx;
    float cy;
};

struct vtriangle {
    point a;
    point b;
    point c;
};

class PointStack {
    vector<point> points;
    int _cursor;
public:

    PointStack() {
        this->_cursor = -1;
    }

    void push(point p) {
        bool same = check(p);
//                if (this->_cursor > -1) {
  //                  for (int i = 0; i <= this->_cursor; i++) {
//                        if ((points[i].x == p.x) && (points[i].y == p.y)) {
//                            same = true;
//                        }
//                   }
//                }

        if (same==0) {
		printf("(%f,%f) %i",p.x,p.y, same);

            _cursor++;
            points.push_back(p);
        }
    }

    point pop() {
        point p = points[_cursor];
        _cursor--;
        points.pop_back();
        return p;
    }

    int size() {
        return points.size();
    }

    bool check(point p){
	bool b=false;
  	for (unsigned int i=0;i<points.size(); i++){
		if ((p.x==points[i].x)&&(p.y==points[i].y)){
			return true;
		}
	}

	return b;
    }

    vector<point> getStack() {
        return points;
    }

};

class Tools {
public:

    /**
     * @param p1
     * @param p2
     * @param p3
     * @see also http://cs.wikipedia.org/wiki/Troj%C3%BAheln%C3%ADk#Obvod_a_obsah
     * @return
     */
    static float calculateTriangleArea(point p1, point p2, point p3) {
        return 0.5 * abs((p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y));
    }

    /**
     * @param p1
     * @param p2
     * @param p3
     * @see also http://cs.wikipedia.org/wiki/Troj%C3%BAheln%C3%ADk#Obvod_a_obsah
     * @return
     */
    static float isPointInTriangle_calculateTriangleArea(point p1, point p2, point p3) {
        return (p1.x - p3.x) * (p2.y - p3.y) - (p1.y - p3.y)*(p2.x - p3.x);
    }

    /**
     * @param pt
     * @param v1
     * @param v2
     * @param v3
     * @see also http://cs.wikipedia.org/wiki/Troj%C3%BAheln%C3%ADk#Obvod_a_obsah
     * @return
     */
    static bool isPointInTriangle(point pt, point a, point b, point c) {
        bool b1, b2, b3, b4;
	float f1,f2,f3,f4;


        if (((a.x==pt.x)&&(a.y==pt.y))||((b.x==pt.x)&&(b.y==pt.y))||((c.x==pt.x)&&(c.y==pt.y))){
              return 0;
        }


        f1 = isPointInTriangle_calculateTriangleArea(a, b, pt);
//	printf("f1:%f\n",f1);
	if (((f1 == 0.0f)||(f1 == 1.f))&&(min(a.x,b.x)<=pt.x)&&(max(a.x,b.x)>=pt.x)&&(min(a.y,b.y)<=pt.y)&&(max(a.y,b.y)>=pt.y)){
//		printf("A\n");
		return 1;
	}else{
		b1=1;
	};
        f2 = isPointInTriangle_calculateTriangleArea(b, c, pt);
	if (((f2 == 0.0f)||(f2 == 1.f))&&(min(b.x,c.x)<=pt.x)&&(max(b.x,c.x)>=pt.x)&&(min(b.y,c.y)<=pt.y)&&(max(b.y,c.y)>=pt.y)){
//		printf("B:\n");
//		dumpPoint(b);
//		dumpPoint(c);
//		dumpPoint(pt);
//		printf("\n\n");
              return 1;
        }else{
//		printf("\nF2: %f; %f<%f %i, %f>%f %i, %f<%f %i, %f>%f %i \n\n",f2, min(b.x,c.x),pt.x, (min(b.x,c.x)<=pt.x), max(b.x,c.x),pt.x,(max(b.x,c.x)>=pt.x), min(b.y,c.y), pt.y,(min(b.y,c.y)<=pt.y), max(b.y,c.y), pt.y, (max(b.y,c.y)>=pt.y));
                b2=1;
        };

        f3 = isPointInTriangle_calculateTriangleArea(c, a, pt);
	if (((f3 == 0.0f)||(f3==1.f))&&(min(c.x,a.x)<=pt.x)&&(max(c.x,a.x)>=pt.x)&&(min(c.y,a.y)<=pt.y)&&(max(c.y,a.y)>=pt.y)){
//		printf("C\n");
              return 1;
        }else{
                b3=1;
        };
        f4 = isPointInTriangle_calculateTriangleArea(a, b, c);
	if (((f4 == 0.0f)||(f4 == 1.f))&&(min(a.x,b.x)<=c.x)&&(max(a.x,b.x)>=c.x)&&(min(a.y,b.y)<=c.y)&&(max(a.y,b.y)>=c.y)){
                return 1;
        }else{
                b4=1;
        };

//	dumpPoint(pt);
//	dumpPoint(a);
//	dumpPoint(b);
//	dumpPoint(c);


	b1=(f1<0);
	b2=(f2<0);
	b3=(f3<0);
	b4=(f4<0);


	if ((f1==0)||(f2==0)||(f3==0)||(f4==0)){
//	printf(" 0 \n");
		return 0;
	}
	
//	printf("\n");
//	printf("xx: %i %i %i %i, %f \n", b1, b2, b3, b4, isPointInTriangle_calculateTriangleArea(a, b, pt));
        return ((b1 == b2) && (b2 == b3) && (b3 == b4));
    }

    /**
     * @param result
     */
    static void printResult(float result) {
        printf("Vysledny obsah: %.4f\n", abs(result));
    }

    /**
     * @param result
     * @return
     */
    static bool sameTriangles(vtriangle A, vtriangle B) {
        bool b1, b2, b3;

        b1 = samePoints(A.a, B.a, B.b, B.c);
        b2 = samePoints(A.b, B.a, B.b, B.c);
        b3 = samePoints(A.c, B.a, B.b, B.c);

        return (b1 && b2 && b3);
    }

    static bool pointsOnLine(point a, point b, point c){
	float r1, r2, r3, d1, d2;

	if (samePoints(a, b) || samePoints(a, c) || samePoints(b, c)){
		return 1;

	}

	r1 = (a.x-b.x)/(a.y-b.y);
	r2 = (b.x-c.x)/(b.y-c.y);
	r3 = (a.x-c.x)/(a.y-c.y);

	d1 = sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
	d2 = sqrt((a.x-c.x)*(a.x-c.x)+(a.y-c.y)*(a.y-c.y));

	if ((r1 == r2)&& (r2 == r3)){
		return (d1>=d2);

	}else{
		return 0;
	}

    }

    static bool existTouchPoint(vtriangle A, vtriangle B) {
	if (pointsOnLine(A.a, A.b, B.a)) {
		return 1;
	}
        if (pointsOnLine(A.a, A.b, B.b)) {
                return 1;
        }
        if (pointsOnLine(A.a, A.b, B.c)) {
                return 1;
        }
        if (pointsOnLine(A.a, A.c, B.a)) {
                return 1;
        }
        if (pointsOnLine(A.a, A.c, B.b)) {
                return 1;
        }
        if (pointsOnLine(A.a, A.c, B.c)) {
                return 1;
        }
        if (pointsOnLine(A.b, A.c, B.a)) {
                return 1;
        }
        if (pointsOnLine(A.b, A.c, B.b)) {
                return 1;
        }
        if (pointsOnLine(A.b, A.c, B.c)) {
                return 1;
        }

	return 0;
    }

    /**
     * @param ax
     * @param ay
     * @param bx
     * @param by
     * @return
     */
    static point getIntersectionOfTwoLines(float ax, float ay, float bx, float by, float cx, float cy, float dx, float dy) {

        float k1,q1, k2, q2, nx, ny;

        if ((ax-bx)!=0){
                k1=(ay-by)/(ax-bx);
        }else{
                k1=9999;
        }

        if (k1>=9999){
                q1=0;
        }else{
                q1=ay-k1*ax;
        }

        if ((cx-dx)!=0){
                k2=(cy-dy)/(cx-dx);
        }else{
                k2=9999;
        }

        if (k2>=9999){
                q2=0;
        }else{
                q2=cy-k2*cx;
        }

	if (ax==bx){
		nx = ax;
	}else if (cx==dx){
		nx = cx;
	}else{
		nx = (q2-q1)/(k1-k2);
	}
	if (ay==by){
		ny = ay;
	}else if (cy == dy){
		ny = cy;
	}else{
	        ny = k1*nx+q1;
	}

	point p;

/*
        if ((min(ax, bx)<=nx)&&(max(ax, bx)>=nx) && (min(cx,dx)<=nx)&&(max(cx,dx)>=nx)&&
            (min(ay, by)<=ny)&&(max(ay, by)>=ny) && (min(cy,dy)<=ny)&&(max(cy,dy)>=ny))
	{
*/
	if (nx>=9999){
		p.x=0;
	}else{
		p.x = nx;
	}
	if (ny>=9999){
		p.y = 0;
	}else{
		p.y = ny;
	}

/*
        }else{
		p.x = ax;
		p.y = ay;
        }
*/	

	return p;	

    }

    /**
     * @param ax
     * @param ay
     * @param bx
     * @param by
     * @param cx
     * @param cy
     * @param dx
     * @param dy
     * @return
     */
    static bool existsIntersectionOfTwoLines(float ax, float ay, float bx, float by, float cx, float cy, float dx, float dy) {
	float k1,q1, k2, q2,nx,ny;

//	printf("\n\nax:[%f,%f]; bx:[%f,%f]; cx:[%f,%f]; dx:[%f,%f];\n\n", ax,ay,bx,by,cx,cy,dx,dy);

	if ((ax-bx)!=0){
		k1=(ay-by)/(ax-bx);
	}else{
		k1=9999;
	}

	if (k1>=9999){
		q1=1;
	}else{
		q1=ay-k1*ax;
	}

        if ((cx-dx)!=0){
                k2=(cy-dy)/(cx-dx);
        }else{
                k2=9999;
        }

        if (k2>=9999){
                q2=1;
        }else{
                q2=cy-k2*cx;
        }

	if (((k1>=9999)||(k2>=9999))){
		if (ax==bx){
                	nx = ax;
	        }else if (cx==dx){
        	        nx = cx;
	        }else{
        	        nx = -1;//(q2-q1)/(k1-k2);
        	}	
	        if (ay==by){
        	        ny = ay;
	        }else if (cy == dy){
        	        ny = cy;
	        }else{
        	        ny = -1;//k1*nx+q1;
	        }
		if ((min(ax, bx)<=nx)&&(max(ax,bx)>=nx)&&
                    (min(ay, by)<=ny)&&(max(ay,by)>=ny)&&
		    (min(cx, dx)<=nx)&&(max(cx,dx)>=nx)&&
		    (min(cy, dy)<=ny)&&(max(cy,dy)>=ny)){
	
			if (!(((ax==nx)&&(ay==ny))||
			    ((bx==nx)&&(by==ny))||
                            ((cx==nx)&&(cy==ny))||
                            ((dx==nx)&&(dy==ny)))){
				return true;
			}
		}	
		
	}

	if (k1==k2){
		if (
			((min(ax, bx)<cx)&&(max(ax, bx)>cx)&&(min(ay, by)<cy)&&(max(ay, by)>cy)) || 
			((min(ax, bx)<dx)&&(max(ax, bx)>dx)&&(min(ay, by)<dy)&&(max(ay, by)>dy)) ||
			((min(cx, dx)<ax)&&(max(cx, dx)>ax)&&(min(cy, dy)<ay)&&(max(cy, dy)>ay)) ||
                        ((min(cx, dx)<bx)&&(max(cx, dx)>bx)&&(min(cy, dy)<by)&&(max(cy, dy)>by))
			){
//				printf("\n\nax:[%f,%f]; bx:[%f,%f]; cx:[%f,%f]; dx:[%f,%f];\n\n", ax,ay,bx,by,cx,cy,dx,dy);
//				printf("k1:%f, q1=%f, k2=%f, q2=%f, nx=%f, ny=%f\n", k1,q1,k2,q2, nx, ny);
				if ((isPointOnLine(cx, ax, bx)&&(isPointOnLine(cy, ay, by)))||
				      	(isPointOnLine(dx, ax, bx)&&(isPointOnLine(dy, ay, by)))||
					(isPointOnLine(ax, cx, dx)&&(isPointOnLine(ay, cy, dy)))||
					(isPointOnLine(bx, cx, dx)&&(isPointOnLine(by, cy, dy)))	
				   ){
					return false;
				}else{
					return true;
				}
			}else{
				return false;
			}
	}

	nx = (q2-q1)/(k1-k2);
	ny = k1*nx+q1; 

	if ((min(ax, bx)<=nx)&&(max(ax, bx)>=nx) && (min(cx,dx)<=nx)&&(max(cx,dx)>=nx)&&
	    (min(ay, by)<=ny)&&(max(ay, by)>=ny) && (min(cy,dy)<=ny)&&(max(cy,dy)>=ny)){
		if ((samePoints(ax,ay,nx,ny)||samePoints(bx,by,nx,ny))|
		   samePoints(cx,cy,nx,ny)||samePoints(dx,dy,nx,ny)){
			return false;
		}
//	printf("XX ax:%f,ay:%f,bx:%f,by:%f,cx:%f,cy:%f,dx:%f,dy:%f,nx:%f,ny:%f\n", ax, ay, bx, by, cx, cy, dx, dy, nx, ny);
		return true;
	}else{
	//	printf("k1:%f, q1=%f, k2=%f, q2=%f, nx=%f, ny=%f\n", k1,q1,k2,q2, nx, ny);
		return false;
	}
    }

    static bool existsIntersectionOfTwoLines(point A, point B, point C, point D){
//	printf("here\n");
	return existsIntersectionOfTwoLines(A.x, A.y, B.x, B.y, C.x, C.y, D.x, D.y)||existsIntersectionOfTwoLines(C.x, C.y, D.x, D.y, A.x, A.y, B.x, B.y);
    }


    /**
     * @param p
     */
    static void dumpPoint(point p) {
        cout << "[" << p.x << "," << p.y << "];";
    }

    /**

     * @param A
     * @param B
     * @return
     */
    static float calculatePolygonArea(vector<point> points) {
        point A;
        point B;
        points.push_back(points[0]);
        A = points[0];
        B = points[1];
        float r = 0;
        int size = 2;
        int pointsize = points.size();
	printf("\nno of points:%i\n", pointsize);

        while (size <= pointsize) {
//            dumpPoint(A);
//            dumpPoint(B);
            r += (A.x * B.y - A.y * B.x);
		printf(" %f ",r);
            A = B;
            B = points[size];
            size += 1;
        }

	printf("\n");
        return r * 0.5;
    }

    /**
     * @param result
     * @return
     */
    static float calculateIntersectedArea(vtriangle A, vtriangle B) {
        PointStack stack;

	    stack.push(A.a);
	    bool opacne=false;
	    bool jedemeB=false;
		point p;


                if (existsIntersectionOfTwoLines(A.a, A.b, B.a,B.c)){
                        p = getIntersectionOfTwoLines(B.a.x, B.a.y, B.c.x, B.c.y, A.a.x, A.a.y, A.b.x, A.b.y);
                        stack.push(p);
                        if (!samePoints(B.c, A.a, A.b, A.c)&&(!isPointInTriangle(B.c, A.a, A.b, A.c))){
                                stack.push(B.a);
                        }else{
                                stack.push(B.c);
                                opacne=true;
                        }
                        if (existsIntersectionOfTwoLines(A.a, A.b, B.a,B.b)&&(!opacne)){
                                p = getIntersectionOfTwoLines(B.a.x, B.a.y, B.b.x, B.b.y, A.a.x, A.a.y, A.b.x, A.b.y);
                                stack.push(p);
                        }else if (existsIntersectionOfTwoLines(A.a, A.b, B.b,B.c)&&opacne){
                                p = getIntersectionOfTwoLines(B.b.x, B.b.y, B.c.x, B.c.y, A.a.x, A.a.y, A.b.x, A.b.y);
                                stack.push(p);
                        }else{
                                jedemeB=true;
                        }
                }else if (existsIntersectionOfTwoLines(A.a, A.b, B.a,B.b)){
			p = getIntersectionOfTwoLines(B.a.x, B.a.y, B.b.x, B.b.y, A.a.x, A.a.y, A.b.x, A.b.y);
			stack.push(p);
			if (!samePoints(B.b, A.a, A.b, A.c)&&(!isPointInTriangle(B.b, A.a, A.b, A.c))){
				stack.push(B.b);
			}else{
				stack.push(B.a);
				opacne=true;
			}
			if (existsIntersectionOfTwoLines(A.a, A.b, B.b,B.c)&&!(opacne)){
				p = getIntersectionOfTwoLines(B.b.x, B.b.y, B.c.x, B.c.y, A.a.x, A.a.y, A.b.x, A.b.y);
				stack.push(p);
			}else if (existsIntersectionOfTwoLines(A.a, A.b, B.a,B.c)&&opacne){
                                p = getIntersectionOfTwoLines(B.a.x, B.a.y, B.c.x, B.c.y, A.a.x, A.a.y, A.b.x, A.b.y);
				stack.push(p);
                        }else{
				jedemeB=true;
			} 
		}else
		if (existsIntersectionOfTwoLines(A.a, A.b, B.b,B.c)){
                        p = getIntersectionOfTwoLines(B.b.x, B.b.y, B.c.x, B.c.y, A.a.x, A.a.y, A.b.x, A.b.y);
                        stack.push(p);
                        if (!samePoints(B.c, A.a, A.b, A.c)&&(!isPointInTriangle(B.c, A.a, A.b, A.c))){
                                stack.push(B.c);
                        }else{
                                stack.push(B.b);
                                opacne=true;
                        }
                        if (existsIntersectionOfTwoLines(A.a, A.b, B.a,B.c)&&(!opacne)){
                                p = getIntersectionOfTwoLines(B.a.x, B.a.y, B.c.x, B.c.y, A.a.x, A.a.y, A.b.x, A.b.y);
                                stack.push(p);
                        }else if (existsIntersectionOfTwoLines(A.a, A.b, B.a,B.b)&&opacne){
                                p = getIntersectionOfTwoLines(B.a.x, B.a.y, B.b.x, B.b.y, A.a.x, A.a.y, A.b.x, A.b.y);
                                stack.push(p);
                        }else{
				jedemeB=true;
			}
		}else
		if (existsIntersectionOfTwoLines(A.a, A.b, B.a,B.c)){
                        p = getIntersectionOfTwoLines(B.a.x, B.a.y, B.c.x, B.c.y, A.a.x, A.a.y, A.b.x, A.b.y);
                        stack.push(p);
                        if (!samePoints(B.c, A.a, A.b, A.c)&&(!isPointInTriangle(B.c, A.a, A.b, A.c))){
                                stack.push(B.a);
                        }else{
                                stack.push(B.c);
                                opacne=true;
                        }
                        if (existsIntersectionOfTwoLines(A.a, A.b, B.a,B.b)&&(!opacne)){
                                p = getIntersectionOfTwoLines(B.a.x, B.a.y, B.b.x, B.b.y, A.a.x, A.a.y, A.b.x, A.b.y);
                                stack.push(p);
                        }else if (existsIntersectionOfTwoLines(A.a, A.b, B.b,B.c)&&opacne){
                                p = getIntersectionOfTwoLines(B.b.x, B.b.y, B.c.x, B.c.y, A.a.x, A.a.y, A.b.x, A.b.y);
                                stack.push(p);
                        }else{
				jedemeB=true;
			}
                }
		if (!isPointInTriangle(A.b, B.a, B.b, B.c)&&(!jedemeB)){
			stack.push(A.b);
		}
		if (jedemeB){
	cout<<"aa\n";
			if ((!isPointInTriangle(B.c, A.a, A.b, A.c))){
				stack.push(B.c);
			}
			if ((!isPointInTriangle(B.a, A.a, A.b, A.c))&&(opacne)){
                                stack.push(B.a);
                        }

		}
cout<<"z B\n";
		if ((jedemeB)&&(existsIntersectionOfTwoLines(A.a, A.b, B.b,B.c))){
			p = getIntersectionOfTwoLines(B.b.x, B.b.y, B.c.x, B.c.y, A.a.x, A.a.y, A.b.x, A.b.y);
                        stack.push(p);
			stack.push(A.b);
		}
		if ((jedemeB)&&(existsIntersectionOfTwoLines(A.a, A.b, B.a,B.c))){
                        p = getIntersectionOfTwoLines(B.a.x, B.a.y, B.c.x, B.c.y, A.a.x, A.a.y, A.b.x, A.b.y);
                        stack.push(p);
                        stack.push(B.b);
                }
		
                if (existsIntersectionOfTwoLines(A.b, A.c, B.a,B.b)){
                        p = getIntersectionOfTwoLines(B.a.x, B.a.y, B.b.x, B.b.y, A.b.x, A.b.y, A.c.x, A.c.y);
                        stack.push(p);
			if (!opacne){
				if (!isPointInTriangle(B.b, A.a, A.b, A.c)){
                                	stack.push(B.b);
				}
                        }else{
				if (!isPointInTriangle(B.a, A.a, A.b, A.c)){
                                	stack.push(B.a);
				}
                        }
                        if (existsIntersectionOfTwoLines(A.b, A.c, B.b,B.c)&&(!opacne)){
                                p = getIntersectionOfTwoLines(B.b.x, B.b.y, B.c.x, B.c.y, A.b.x, A.b.y, A.c.x, A.c.y);
                                stack.push(p);
                        }else if (existsIntersectionOfTwoLines(A.b, A.c, B.a,B.c)&&opacne){
                                p = getIntersectionOfTwoLines(B.a.x, B.a.y, B.c.x, B.c.y, A.b.x, A.b.y, A.c.x, A.c.y);
                                stack.push(p);
                        }
                }else
                if (existsIntersectionOfTwoLines(A.b, A.c, B.b,B.c)){
                        p = getIntersectionOfTwoLines(B.b.x, B.b.y, B.c.x, B.c.y, A.b.x, A.b.y, A.c.x, A.c.y);
                        stack.push(p);
			if (!opacne){
                                stack.push(B.c);
                        }else{
                                stack.push(B.b);
                        }
                        if (existsIntersectionOfTwoLines(A.b, A.c, B.a,B.c)&&(!opacne)){
                                p = getIntersectionOfTwoLines(B.a.x, B.a.y, B.c.x, B.c.y, A.b.x, A.b.y, A.c.x, A.c.y);
                                stack.push(p);
                        }else if (existsIntersectionOfTwoLines(A.b, A.c, B.a,B.b)&&opacne){
                                p = getIntersectionOfTwoLines(B.a.x, B.a.y, B.b.x, B.b.y, A.b.x, A.b.y, A.c.x, A.c.y);
                                stack.push(p);
                        }

                }else
                if (existsIntersectionOfTwoLines(A.b, A.c, B.a,B.c)){
                        p = getIntersectionOfTwoLines(B.a.x, B.a.y, B.c.x, B.c.y, A.b.x, A.b.y, A.c.x, A.c.y);
                        stack.push(p);
                        if (!samePoints(B.c, A.a, A.b, A.c)&&(!isPointInTriangle(B.c, A.a, A.b, A.c))){
				if (!isPointInTriangle(B.a, A.a, A.b, A.c)){	
                                	stack.push(B.a);
				}
                        }else{
                                if (!isPointInTriangle(B.c, A.a, A.b, A.c)){
					stack.push(B.c);
				}
                        }
                        if (existsIntersectionOfTwoLines(A.a, A.c, B.a,B.b)&&(!opacne)){
                                p = getIntersectionOfTwoLines(B.a.x, B.a.y, B.b.x, B.b.y, A.a.x, A.a.y, A.c.x, A.c.y);
                                stack.push(p);
                        }else if (existsIntersectionOfTwoLines(A.a, A.c, B.b,B.c)&&opacne){
                                p = getIntersectionOfTwoLines(B.b.x, B.b.y, B.c.x, B.c.y, A.a.x, A.a.y, A.c.x, A.c.y);
                                stack.push(p);
                        }

                }

                if (!isPointInTriangle(A.c, B.a, B.b, B.c)){
                        stack.push(A.c);
		}
	
cout<<"z C\n";

		
                if (existsIntersectionOfTwoLines(A.a, A.c, B.b,B.c)){
                        p = getIntersectionOfTwoLines(B.b.x, B.b.y, B.c.x, B.c.y, A.a.x, A.a.y, A.c.x, A.c.y);
                        stack.push(p);
                        if (!opacne){
                                stack.push(B.c);
                        }else{
                                stack.push(B.b);
                        }
                        if (existsIntersectionOfTwoLines(A.a, A.c, B.a,B.c)&&(!opacne)){
                                p = getIntersectionOfTwoLines(B.a.x, B.a.y, B.c.x, B.c.y, A.a.x, A.a.y, A.c.x, A.c.y);
                                stack.push(p);
                        }else if (existsIntersectionOfTwoLines(A.a, A.c, B.a,B.b)&&opacne){
                                p = getIntersectionOfTwoLines(B.a.x, B.a.y, B.b.x, B.b.y, A.a.x, A.a.y, A.c.x, A.c.y);
                                stack.push(p);
                        }


                }else

                if (existsIntersectionOfTwoLines(A.a, A.c, B.a,B.c)){
                        p = getIntersectionOfTwoLines(B.a.x, B.a.y, B.c.x, B.c.y, A.a.x, A.a.y, A.c.x, A.c.y);
                        stack.push(p);
                        if (!samePoints(B.c, A.a, A.b, A.c)&&(!isPointInTriangle(B.c, A.a, A.b, A.c))){
                                stack.push(B.a);
                        }else{
                                stack.push(B.c);
                        }
                        if (existsIntersectionOfTwoLines(A.a, A.c, B.a,B.b)&&(!opacne)){
                                p = getIntersectionOfTwoLines(B.a.x, B.a.y, B.b.x, B.b.y, A.a.x, A.a.y, A.c.x, A.c.y);
                                stack.push(p);
                        }else if (existsIntersectionOfTwoLines(A.a, A.c, B.b,B.c)&&opacne){
                                p = getIntersectionOfTwoLines(B.b.x, B.b.y, B.c.x, B.c.y, A.a.x, A.a.y, A.c.x, A.c.y);
                                stack.push(p);
                        }

                }else
                if (existsIntersectionOfTwoLines(A.a, A.c, B.a,B.b)){
                        p = getIntersectionOfTwoLines(B.a.x, B.a.y, B.b.x, B.b.y, A.a.x, A.a.y, A.c.x, A.c.y);
                        stack.push(p);
                        if (!opacne){
                                stack.push(B.b);
                        }else{
                                stack.push(B.a);
                        }
                        if (existsIntersectionOfTwoLines(A.a, A.c, B.b,B.c)&&(!opacne)){
                                p = getIntersectionOfTwoLines(B.b.x, B.b.y, B.c.x, B.c.y, A.a.x, A.a.y, A.c.x, A.c.y);
                                stack.push(p);
                        }else if (existsIntersectionOfTwoLines(A.a, A.c, B.a,B.c)&&opacne){
                                p = getIntersectionOfTwoLines(B.a.x, B.a.y, B.c.x, B.c.y, A.a.x, A.a.y, A.c.x, A.c.y);
                                stack.push(p);
                        }

                }else
                if (existsIntersectionOfTwoLines(A.a, A.c, B.b,B.c)){
                        p = getIntersectionOfTwoLines(B.b.x, B.b.y, B.c.x, B.c.y, A.a.x, A.a.y, A.c.x, A.c.y);
                        stack.push(p);
                        if (!opacne){
                                stack.push(B.c);
                        }else{
                                stack.push(B.b);
                        }
                        if (existsIntersectionOfTwoLines(A.a, A.c, B.a,B.c)&&(!opacne)){
                                p = getIntersectionOfTwoLines(B.a.x, B.a.y, B.c.x, B.c.y, A.a.x, A.a.y, A.c.x, A.c.y);
                                stack.push(p);
                        }else if (existsIntersectionOfTwoLines(A.a, A.c, B.a,B.b)&&opacne){
                                p = getIntersectionOfTwoLines(B.a.x, B.a.y, B.b.x, B.b.y, A.a.x, A.a.y, A.c.x, A.c.y);
                                stack.push(p);
                        }


                }

        if (stack.size() <= 0) return 99999;

        return calculatePolygonArea(stack.getStack());
    }

    /**
     * @param result
     * @return
     */
    static bool existsIntersections(vtriangle A, vtriangle B) {
        bool a1, a2, a3;
        bool b1, b2, b3,c1,c2,c3;

        a1 = isPointInTriangle(A.a, B.a, B.b, B.c);//||samePoints(A.a, B.a, B.b, B.c);;
        a2 = isPointInTriangle(A.b, B.a, B.b, B.c);//||samePoints(A.b, B.a, B.b, B.c);;
        a3 = isPointInTriangle(A.c, B.a, B.b, B.c);//||samePoints(A.c, B.a, B.b, B.c);;


        b1 = isPointInTriangle(B.a, A.a, A.b, A.c);//||samePoints(B.a, A.a, A.b, A.c);
        b2 = isPointInTriangle(B.b, A.a, A.b, A.c);//||samePoints(B.b, A.a, A.b, A.c);
        b3 = isPointInTriangle(B.c, A.a, A.b, A.c);//||samePoints(B.c, A.a, A.b, A.c);

	a1 = existsIntersectionOfTwoLines(A.a, A.b, B.a, B.b);
        a2 = existsIntersectionOfTwoLines(A.a, A.c, B.a, B.b);
        a3 = existsIntersectionOfTwoLines(A.b, A.c, B.a, B.b);
        b1 = existsIntersectionOfTwoLines(A.a, A.b, B.a, B.c);
        b2 = existsIntersectionOfTwoLines(A.a, A.c, B.a, B.c);
        b3 = existsIntersectionOfTwoLines(A.b, A.c, B.a, B.c);
        c1 = existsIntersectionOfTwoLines(A.a, A.b, B.b, B.c);
        c2 = existsIntersectionOfTwoLines(A.a, A.c, B.b, B.c);
        c3 = existsIntersectionOfTwoLines(A.b, A.c, B.b, B.c);

	printf("%i, %i, %i, %i, %i, %i, %i, %i, %i\n", a1,a2,a3,b1,b2,b3,c1,c2,c3);

        return (a1 || a2 || a3 || b1 || b2 || b3 || c1 || c2 || c3);
    }

    /**
     * @param A
     * @param B
     * @return
     */
    static bool existsTriangleInTriangle(vtriangle A, vtriangle B) {
        bool a1, a2, a3;
        bool b1, b2, b3;

        a1 = isPointInTriangle(A.a, B.a, B.b, B.c);
        a2 = isPointInTriangle(A.b, B.a, B.b, B.c);
        a3 = isPointInTriangle(A.c, B.a, B.b, B.c);

        b1 = isPointInTriangle(B.a, A.a, A.b, A.c);
        b2 = isPointInTriangle(B.b, A.a, A.b, A.c);
        b3 = isPointInTriangle(B.c, A.a, A.b, A.c);

        if (a1 && a2 && a3) {
/*
		printf("1<< ");
		dumpPoint(A.a);
		dumpPoint(A.b);
		dumpPoint(A.c);
		printf(" =%i= ", a2);
		dumpPoint(B.a);
		dumpPoint(B.b);
		dumpPoint(B.c);
		printf("<<\n");
*/
            return true;
        } else if (b1 && b2 && b3 ) {
//		printf("2<<");
            return true;
        } else {
//		printf("nic %i, %i, %i = %i, %i, %i\n", a1, a2, a3, b1, b2, b3);
            return false;
        }
    }

    /**
     * @param A
     * @param B
     * @return
     */
    static vtriangle getTriangleInTriangle(vtriangle A, vtriangle B) {
        bool a1, a2, a3;
        bool b1, b2, b3;

        a1 = isPointInTriangle(A.a, B.a, B.b, B.c);
        a2 = isPointInTriangle(A.b, B.a, B.b, B.c);
        a3 = isPointInTriangle(A.c, B.a, B.b, B.c);

        b1 = isPointInTriangle(B.a, A.a, A.b, A.c);
        b2 = isPointInTriangle(B.b, A.a, A.b, A.c);
        b3 = isPointInTriangle(B.c, A.a, A.b, A.c);

        if (a1 && a2 && a3) {
            return B;
        } else {
            return A;
        }
    }

    /**
     * @param p
     * @param p1
     * @param p2
     * @param p3
     * @return
     */
    static bool isPointOnLine(point t, point a, point b) {
        float result1, result2;
        result1 = (t.x - a.x) / (b.x - a.x);
	result2 = (t.y - a.y) / (b.y - a.y);
	
        return ((result1 >= 0 && result1 <= 1 && result2 >= 0 && result2 <=1));
    }

    static bool isPointOnLine(float tx, float ax, float bx) {
        float result;
        result = (tx - ax) / (bx - ax);
        return ((result >= 0 && result <= 1));
    }


    /**
     * @param result
     * @return
     */
    static bool existsTouchingPoints(vtriangle A, vtriangle B) {

        // Checking .. T1, point A
        float t1a1 = isPointOnLine(A.a.x, B.a.x, B.b.x);
        float t1a2 = isPointOnLine(A.a.x, B.b.x, B.c.x);
        float t1a3 = isPointOnLine(A.a.x, B.c.x, B.a.x);

        // Checking .. T1, point B
        float t1b1 = isPointOnLine(A.b.x, B.a.x, B.b.x);
        float t1b2 = isPointOnLine(A.b.x, B.b.x, B.c.x);
        float t1b3 = isPointOnLine(A.b.x, B.c.x, B.a.x);

        // Checking .. T1, point C
        float t1c1 = isPointOnLine(A.c.x, B.a.x, B.b.x);
        float t1c2 = isPointOnLine(A.c.x, B.b.x, B.c.x);
        float t1c3 = isPointOnLine(A.c.x, B.c.x, B.a.x);

        // Checking .. T2, point A
        float t2a1 = isPointOnLine(B.a.x, A.a.x, A.b.x);
        float t2a2 = isPointOnLine(B.a.x, A.b.x, A.c.x);
        float t2a3 = isPointOnLine(B.a.x, A.c.x, A.a.x);

        // Checking .. T2, point B
        float t2b1 = isPointOnLine(B.b.x, A.a.x, A.b.x);
        float t2b2 = isPointOnLine(B.b.x, A.b.x, A.c.x);
        float t2b3 = isPointOnLine(B.b.x, A.c.x, A.a.x);

        // Checking .. T2, point C
        float t2c1 = isPointOnLine(B.c.x, A.a.x, A.b.x);
        float t2c2 = isPointOnLine(B.c.x, A.b.x, A.c.x);
        float t2c3 = isPointOnLine(B.c.x, A.c.x, A.a.x);

        if ((t1a1) || (t1a2) || (t1a3) || (t1b1) || (t1b2) || (t1b3) || (t1c1)
                || (t1c2) || (t1c3) || (t2a1) || (t2a2) || (t2a3) || (t2b1)
                || (t2b2) || (t2b3) || (t2c1) || (t2c2) || (t2c3)) {
            return true;
        }

        return false;
    }

    /**
     * @param a
     * @param b
     * @return
     */
    static bool samePoints(point p, point p1, point p2, point p3) {
        if ((p.x == p1.x && p.y == p1.y) || (p.x == p2.x && p.y == p2.y) || (p.x == p3.x && p.y == p3.y)) {
            return true;
        } else {
            return false;
        }
    }

    static bool samePoints(point p, point p1) {
        if ((p.x == p1.x && p.y == p1.y)) {
            return true;
        } else {
            return false;
        }
    }

    static bool samePoints(float ax, float ay, float bx,float by){
	point p1, p2;
	p1.x=ax;
	p1.y=ay;
	p2.x=bx;
	p2.y=by;
	return samePoints(p1, p2);
    }

    /**
     * @param a
     * @param b
     * @return
     */
    static bool isEquals(float a, float b) {
        return fabs(a - b) <= 1000 * numeric_limits<double>::epsilon();
    }

};

/* Default messages */
string INPUT_ERROR_MESSAGE = "Spatny vstup.\n";
string NO_TOUCHING_MESSAGE = "Trojuhelniky se nedotykaji.\n";

int main(int argc, char** argv) {

    // Triangles
    vtriangle A;
    vtriangle B;

    // Points
    point A1;
    point B1;
    point C1;
    point A2;
    point B2;
    point C2;

    //float result;

    //==========================================================================
    // VALIDATING INPUTS
    //==========================================================================

	printf("A\n");
    int numpoints = 0;

    // Parse points
    numpoints = scanf("%f %f %f %f %f %f %f %f %f %f %f %f", &A1.x, &A1.y, &B1.x, &B1.y, &C1.x, &C1.y, &A2.x, &A2.y, &B2.x, &B2.y, &C2.x, &C2.y);

    if (numpoints != 12) {
        cout << "[error #3]" << endl;
        cout << INPUT_ERROR_MESSAGE;
        return 1;
    }

    float offsetX=0.0;
    float offsetY=0.0;
/*
    if (A1.x<0){
	offsetX=A1.x;
    }
    if (A1.y<0){
	offsetY=A1.y;
    }
    if (B1.x<offsetX){
        offsetX=B1.x;
    }
    if (B1.y<offsetY){
        offsetY=B1.y;
    }
    if (C1.x<offsetX){
        offsetX=C1.x;
    }
    if (C1.y<offsetY){
        offsetY=C1.y;
    }
    if (A2.x<offsetX){
        offsetX=A2.x;
    }
    if (A2.y<offsetY){
        offsetY=A2.y;
    }
    if (B2.x<offsetX){
        offsetX=B2.x;
    }
    if (B2.y<offsetY){
        offsetY=B2.y;
    }
    if (C2.x<offsetX){
        offsetX=C2.x;
    }
    if (C2.y<offsetY){
        offsetY=C2.y;
    }
*/


    // Assing points to triangles
    A.a.x = A1.x-offsetX;
    A.a.y = A1.y-offsetY;
    A.b.x = B1.x-offsetX;
    A.b.y = B1.y-offsetY;
    A.c.x = C1.x-offsetX;
    A.c.y = C1.y-offsetY;

    B.a.x = A2.x-offsetX;
    B.a.y = A2.y-offsetY;
    B.b.x = B2.x-offsetX;
    B.b.y = B2.y-offsetY;
    B.c.x = C2.x-offsetX;
    B.c.y = C2.y-offsetY;

    //==========================================================================
    // CALCULATING
    //==========================================================================

//	printf("1\n");

    if (Tools::sameTriangles(A, B)) {
        // 1) Check same values
	printf("a:\n");
        Tools::printResult(Tools::calculateTriangleArea(A.a, A.b, A.c));
    }else if (Tools::existsIntersections(A, B)) {
	printf("2\n");
        // 3) Check points intersections

        // Triangle in Triangle
        if (Tools::existsTriangleInTriangle(A, B)) {
	    printf("b:\n");
            vtriangle T = Tools::getTriangleInTriangle(A, B);
            Tools::printResult(Tools::calculateTriangleArea(T.a, T.b, T.c));
            return 0;
        }
	printf("4:\n");
        Tools::printResult(Tools::calculateIntersectedArea(A, B));

    } else  if (Tools::existsTriangleInTriangle(A, B)) {
            printf("b2:\n");
            vtriangle T = Tools::getTriangleInTriangle(A, B);
            Tools::printResult(Tools::calculateTriangleArea(T.a, T.b, T.c));
            return 0;
    } else if (Tools::existTouchPoint(A, B)){
        printf("3\n");
        Tools::printResult(Tools::calculateTriangleArea(A.a, A.b, A.c)+Tools::calculateTriangleArea(B.a, B.b, B.c));


    } else {
        // 4) No touching detect
        cout << NO_TOUCHING_MESSAGE;
    }

    return 0;
}
