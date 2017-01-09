class UnusualAdd {
public:
    int addAB(int A, int B) {
        // write code here
        
        do{
            int tmp = A & B;
            A = A ^ B;
            B = tmp << 1;
        }while(B != 0);
        
        return A;
    }
};