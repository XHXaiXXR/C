class Cards {
public:
    int cardGame(vector<int> A, int n) {
        // write code here
        vector<vector<int>> F(n, vector<int>(n, 0));
        vector<vector<int>> S(n, vector<int>(n, 0));
        
        for(int i = 0;i < n;i++){
            F[i][i] = A[i];
        }
        
        for(int i = n-2;i >= 0;i--){
            for(int j = i+1;j <= n-1;j++){
                F[i][j] = max(A[i] + S[i+1][j], A[j] + S[i][j-1]);
                S[i][j] = min(F[i+1][j], F[i][j-1]);
            }
        }
        
        return max(F[0][n-1], S[0][n-1]);
    }
};