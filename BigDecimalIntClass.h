#include <iostream>
#include <bits/stdc++.h>
using namespace std;
class BigDecimalInt {
private :
    string num ;
    bool sign ;
public :
    BigDecimalInt () {num="0";sign=1;}
    BigDecimalInt (string s)
    {
        bool valid=1;
        bool prefix = (s[0]=='-'||s[0]=='+') ;
        for (int i= prefix ; i<s.size(); i++ )
        {
            if ( (s[i]-'0') > 9 || (s[i]-'0') < 0 )
            {
               valid=0 ;
               break ;
            }
        }
        if (valid)
        {
            num=s.substr(prefix,s.size()-prefix);
            sign=(s[0] != '-');
        }
        else
        {
            cout<<"this is not a valid number\n";
        }
    }
    BigDecimalInt (int n )
    {
        num=to_string(abs(n));
        sign=(n >= 0);
    }
    friend bool operator > (BigDecimalInt num1 , BigDecimalInt num2)
    {
         if( ! num1.sign && num2.sign )
         {
             return ( false );
         }
         else if ( num1.sign && ! num2.sign )
         {
             return ( true ) ;
         }

         else if (! num1.sign && ! num2.sign )
         {
             return ( num1.num < num2.num ) ;
         }
         else
         {
             return  ( num1.num > num2.num );
         }
    }
    friend bool operator < (BigDecimalInt num1 , BigDecimalInt num2)
    {
        if( ! num1.sign && num2.sign )
         {
             return ( true );
         }
         else if ( num1.sign && ! num2.sign )
         {
             return ( false ) ;
         }

         else if (! num1.sign && ! num2.sign )
         {
             return  ( num1.num > num2.num );
         }
         else
         {
             return  ( num1.num < num2.num );
         }

    }
    friend bool operator == (BigDecimalInt num1 , BigDecimalInt num2)
    {
        return (    (   ( num1.sign == num2.sign )  &&  (  num1.num == num2.num )   ) ? ( true ) : ( false ) ) ;
    }
    friend ostream& operator << (ostream& out, BigDecimalInt n)
    {
        if (!n.sign)
        {
            cout<<'-';
        }
        cout<<n.num;
    }
    int Sign ( BigDecimalInt n )
    {
        if (n.sign)
        {
            return ( 1 ) ;
        }
        else
        {
            return ( -1 ) ;
        }
    }
    int Size ( BigDecimalInt n )
    {
        return ( n.num.size() ) ;
    }
     BigDecimalInt operator=   ( BigDecimalInt n2 )
    {
        num=n2.num ;
        sign=n2.sign ;
    }
    string add ( string first , string second )
    {
        reverse(first.begin() , first.end());
        reverse(second.begin(), second.end());
        first+="0";
        string ans = "" ;
        for ( int i=0 ; i<first.size(); i++)
        {
            int curr = first[i]-'0';
            if (i < second.size () )
            {
                curr += second[i]-'0' ;
            }
            if (curr >= 10 ) first [i+1] ++ ;
            curr%=10;
            ans+=  (char)('0'+curr) ;
        }
        reverse(ans.begin(), ans.end());
        int i=0 ;
        for ( i ; i<ans.size()-1; i++)
        {
            if (ans[i]!='0') return ( ans.substr(i,ans.size()-i) ) ;
        }
        return ( ans.substr(i,ans.size()-i) ) ;
    }
    string sub ( string first , string second )
    {
        reverse(first.begin() , first.end());
        reverse(second.begin(), second.end());
        string ans = "" ;
        for ( int i=0 ; i<first.size(); i++)
        {
            int curr = first[i]-'0';
            if (i < second.size () )
            {
                if (curr >= ( second[i] - '0') )
                {
                    curr-=( second[i] - '0');
                }
                else
                {
                    first [i+1]--;
                    curr+=10;
                    curr-=( second[i] - '0');
                }
            }
            ans+=(char)('0'+curr);
        }
        reverse(ans.begin(), ans.end());
        int i=0 ;
        for ( i ; i<ans.size()-1; i++)
        {
            if (ans[i]!='0') return ( ans.substr(i,ans.size()-i) ) ;
        }
        return ( ans.substr(i,ans.size()-i) ) ;
    }
    BigDecimalInt operator +  (BigDecimalInt n1 )
    {
        BigDecimalInt result ;
        if ( ( !n1.sign &&  ! sign) || (  n1.sign &&  sign) )
        {
            result.sign= (  n1.sign &&   sign ) ;
            if (n1.num> num)
            {
            result.num= add( n1.num , num );
            }
            else
            {
            result.num= add( num , n1.num );
            }
        }
        else
        {
            if (n1.num > num)
            {
                result.sign = ( n1.sign );
                result.num = sub( n1.num , num );
            }
            else
            {
                result.sign = ( sign );
                result.num = sub( num, n1.num );
            }
        }
        return result ;
    }
    BigDecimalInt operator - (BigDecimalInt n1 )
    {
        BigDecimalInt result ;
        if ( ( n1.sign &&  ! sign) || ( ! n1.sign &&  sign) )
        {
            result.sign = (   ! n1.sign &&   sign ) ;
            if (n1.num> num)
            {
            result.num= add( n1.num , num );
            }
            else
            {
            result.num= add( num , n1.num );
            }
        }
        else
        {
            if ( (n1.num.size()>num.size() ) || ( (n1.num.size()==num.size() ) && (n1.num > num) ) )
            {
                result.sign = ( ! n1.sign );
                result.num = sub( n1.num, num );
            }
            else
            {
                result.sign = ( sign );
                result.num = sub( num, n1.num );
            }
        }
        return result ;
    }
    string GetNum () {return num;}
    bool GetSign () {return sign;}
    void SetNum (string s) { num=s;}
    void SetSign (bool b) {sign=b;}

};
