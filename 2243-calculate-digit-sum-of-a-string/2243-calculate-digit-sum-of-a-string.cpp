class Solution {
public:
    string digitSum(string s, int k) {
        while((int)s.size()>k){
            string x="";
            for(int i=0;i<(int)s.size();i+=k){
                int y=0;
                for(int j=i;j<min((int)s.size(),i+k);j++) y+=s[j]-'0';
                x+=to_string(y);
            }
            s=x;
        }
        return s;
    }
};