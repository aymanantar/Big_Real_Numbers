#include "BigDecimalIntClass.h"
using namespace std;
string CleanZeros (string s)
{
    int st , e ;
    string ns ="";
    for (int i=0 ; i<s.size() ; i++)
    {
        if (s[i]!='0'){st=i; break;}
    }
    for (int i=s.size()-1 ; i>=0 ; i--)
    {
        if (s[i]!='0'){e=i; break;}
    }
    cout<<st<<' '<<e<<' '<<s.substr(st,e+1)<<endl;
    return ( s.substr(st,e+1) );

}
class BigReal : public BigDecimalInt
{
private :
    long long PointPosition ;
public :
    BigReal (){}
    BigReal (int n ) : BigDecimalInt(n)
    {
        PointPosition = GetNum().size() ;
    }
    BigReal (string s)
    {
        int get = -1;
        for (int i=0 ; i<s.size() ; i++)
        {
            if (s[i]=='.')
            {
                get = i ;
                break;
            }
        }
        if (get == -1 )
        {
            SetNum ( s );
            PointPosition =  s.size() ;
            //string cons =  CleanZeros( s ) ;
           // BigDecimalInt CleanZeros( s );
        }
        else
        {
            SetNum( s.substr( 0 , get ) + s.substr( get + 1 , s.size() - get - 1  ) ) ;
            PointPosition = get ;
        }
    }
    BigReal ( double n )
    {
        cout<<"should | "<<to_string(n)<<endl;
        BigReal ( to_string ( n ) ) ;
    }
    void operator = (BigReal num1)
    {
        SetNum(num1.GetNum());
        SetSign(num1.GetSign());
        SetPos(num1.GetPos());
    }
    friend ostream& operator << ( ostream &out , BigReal num1 );
    friend bool operator > (BigReal num1 , BigReal num2);
    friend bool operator < (BigReal num1 , BigReal num2);
    friend bool operator == (BigReal num1 , BigReal num2);
    BigReal operator + (BigReal n1 )
    {
       BigReal result ;
       BigDecimalInt l1,r1, l2,r2 , l , r ;
       l1.SetNum( GetNum().substr ( 0 , PointPosition  ) );
       r1.SetNum( GetNum().substr (PointPosition  , GetNum().size() - PointPosition  ));
       l1.SetSign ( GetSign() );
       r1.SetSign ( GetSign() );
       l2.SetNum (n1.GetNum().substr ( 0 , n1.PointPosition  ) ) ;
       r2.SetNum (n1.GetNum().substr (n1.PointPosition  , n1.GetNum().size() - n1.PointPosition  ));
       l2.SetSign( n1.GetSign() );
       r2.SetSign( n1.GetSign() );
       l = l1 + l2 ;
       r = r1 + r2 ;
       result.SetSign ( l.GetSign() ) ;
       result.PointPosition = l.GetNum().size();
       result.SetNum( l.GetNum()+r.GetNum() );
       return result ;
    }
    BigReal operator - (BigReal n1 )
    {
       BigReal result ;
       BigDecimalInt l1,r1, l2,r2 , l , r ;
       l1.SetNum( GetNum().substr ( 0 , PointPosition  ) );
       r1.SetNum( GetNum().substr (PointPosition  , GetNum().size() - PointPosition  ));
       l1.SetSign ( GetSign() );
       r1.SetSign ( GetSign() );
       l2.SetNum (n1.GetNum().substr ( 0 , n1.PointPosition  ) ) ;
       r2.SetNum (n1.GetNum().substr (n1.PointPosition  , n1.GetNum().size() - n1.PointPosition  ));
       l2.SetSign( n1.GetSign() );
       r2.SetSign( n1.GetSign() );
       l = l1 - l2 ;
       r = r1 - r2 ;
       result.SetSign ( l.GetSign() ) ;
       result.PointPosition = l.GetNum().size();
       result.SetNum( l.GetNum()+r.GetNum() );
       return result ;
    }
void SetPos (long long p)
{
    PointPosition = p ;
}
long long GetPos ()
{
    return PointPosition;
}
};
ostream& operator<< ( ostream& out , BigReal num1 )
{
    if (!num1.GetSign())cout<<'-';
    out<<num1.GetNum().substr(0 , num1.GetPos()  )<<'.'<<num1.GetNum().substr (num1.GetPos() , num1.GetNum().size() - num1.GetPos()  );
    return out ;
}
bool operator > (BigReal num1 , BigReal num2)
{
    if (num1.PointPosition>num2.PointPosition)
    {
        return 1 ;
    }
    else if (num1.PointPosition<num2.PointPosition)
    {
        return 0 ;
    }
    else
    {
        BigDecimalInt l1 (num1.GetNum().substr(0, num1.PointPosition) ) , l2 (num2.GetNum().substr(0, num2.PointPosition) )  ;
        if (l1>l2)
        {
            return 1;
        }
        else if (l1<l2)
        {
            return 0;
        }
        else
        {
           BigDecimalInt r1 (num1.GetNum().substr( num1.PointPosition, num1.GetNum().size()-num1.PointPosition ) ) , r2 (num2.GetNum().substr( num2.PointPosition , num2.GetNum().size()-num2.PointPosition) )  ;
            if (r1>r2)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
}
bool operator < (BigReal num1 , BigReal num2)
{
    if (num1.PointPosition<num2.PointPosition)
    {
        return 1 ;
    }
    else if (num1.PointPosition>num2.PointPosition)
    {
        return 0 ;
    }
    else
    {
        BigDecimalInt l1 (num1.GetNum().substr(0, num1.PointPosition) ) , l2 (num2.GetNum().substr(0, num2.PointPosition) )  ;
        if (l1<l2)
        {
            return 1;
        }
        else if (l1>l2)
        {
            return 0;
        }
        else
        {
           BigDecimalInt r1 (num1.GetNum().substr( num1.PointPosition, num1.GetNum().size()-num1.PointPosition ) ) , r2 (num2.GetNum().substr( num2.PointPosition , num2.GetNum().size()-num2.PointPosition) )  ;
            if (r1<r2)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
}
bool operator == (BigReal num1 , BigReal num2)
{
    return ( (num1.PointPosition==num2.PointPosition) && (num1.GetSign()==num2.GetSign()) && (num1.GetNum()==num2.GetNum()) ) ;
}
int main()
{
   // testing .............
    BigReal b ("3.0");
    BigReal a ("3.0");
    BigReal c ;
    c=( b - a ) ;
    cout<<( (b==a)?"yaaaao " : "nooo");
        cout<<( (b>a)?"yaaaao " : "nooo");
            cout<<( (b<a)?"yaaaao " : "nooo");
    cout<<c<<endl;
    return 0;
}
