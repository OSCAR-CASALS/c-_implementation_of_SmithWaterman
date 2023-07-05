#include<iostream>
#include<cstring>
#include<stack>
using namespace std;


int main(){
    cout << "Input first sequence:" << endl;
    string seq_2;
    cin >> seq_2;
    cout << "Input second sequence:" << endl;
    string seq_1;
    cin >> seq_1;
    cout << "Input gap penalty:" << endl;
    float gap;
    cin >> gap;
    cout << "Input match score:" << endl;
    float match;
    cin >> match;
    cout << "Input missmatch penalty:" << endl;
    float missmatch;
    cin >> missmatch;
    cout << "computing alignment..." << endl;
    //Initialise substitution matrix.
    float sub_matrix[int(seq_1.size()) + 1][int(seq_2.size()) + 1];
    memset(sub_matrix, 0, sizeof(sub_matrix));
    //Iterate through all the cells of the substitution matrix with the exception of the first row and column, in each iteration the score for each cell is computed and the maximum score is kept track on.
    float maximum_score = 0.0;
    int max_pos_x = 0;
    int max_pos_y = 0;
    for (int row = 1; row < (int(seq_1.size()) + 1); row++){
        char nucl = seq_1[row - 1];
        for (int col = 1; col < (int(seq_2.size()) + 1); col++){
            //Checking if the nucleotides of each sequence match or not
            float m_score = 0;
            if (nucl == seq_2[col - 1]){
                m_score = match;
            }
            else{
                m_score = -missmatch;
            }
            //Computing the score based on the neighbouring nucleotides taking into account the match/missmatch score and the gap penalties. Then selecting the biggest one for the matrix, if all scores are lower than 0 then the value that the matrix will have is 0.
            float diag = sub_matrix[row-1][col-1] + m_score;
            float above = sub_matrix[row - 1][col] - gap;
            float left = sub_matrix[row][col-1] - gap;
            float score = max(max(diag, max(above, left)), 0.0f);
            sub_matrix[row][col] = score;
            //checking if the score computed is bigger than the actual maximum one, if it is then this value is updated.
            if(score > maximum_score){
                maximum_score = score;
                max_pos_x = row;
                max_pos_y = col;
            }
        }
    }
    //Traceback.
    stack<char> out_1;
    stack<char> out_2;
    stack<int> positions;
    stack<int> score;
    //From the highest score I traverse the matrix backwards till I have reached an score of 0.
    while (maximum_score != 0){
        //Annotating the nucleotides at the position we are currently looking
        out_1.push(seq_1[max_pos_x - 1]);
        out_2.push(seq_2[max_pos_y - 1]);
        positions.push(max_pos_y - 1);
        score.push(maximum_score);
        //Traceback. Here I decide the direction where the next step will be done, this is the one of the neighbouring cell with highest score(only taking into account the cells left, diagonally left, and above of the cell we are currently at).
        int pos_x = 0;
        int pos_y = 0;
        float left_score = sub_matrix[max_pos_x][max_pos_y - 1];
        float diag_score = sub_matrix[max_pos_x - 1][max_pos_y - 1];
        if(left_score > diag_score){
            maximum_score = left_score;
            pos_x = max_pos_x;
            pos_y = max_pos_y - 1;
        }
        else{
            maximum_score = diag_score;
            pos_x = max_pos_x - 1;
            pos_y = max_pos_y - 1;
        }
        float above_score = sub_matrix[max_pos_x - 1][max_pos_y];
        if (maximum_score < above_score){
            maximum_score = above_score;
            pos_x = max_pos_x - 1;
            pos_y = max_pos_y;
        }
        max_pos_x = pos_x;
        max_pos_y = pos_y;
    }
    string f_seq = "";
    string f_seq_2 = "";
    string poss = "";
    string sc = "";
    while (positions.empty() == false)
    {
        char nucl1 = out_1.top();
        out_1.pop();
        char nucl2 = out_2.top();
        out_2.pop();
        if(nucl1 != nucl2){
            nucl2 = '-';
        }
        f_seq_2 += nucl2;
        f_seq += nucl1;
        poss += to_string(positions.top()) + ' ';
        positions.pop();
        sc += to_string(score.top()) + ' ';
        score.pop();

    }
    cout << "sequence 1: " <<  f_seq_2 << endl;
    cout << "sequence 2: " << f_seq << endl;
    cout << "positions: " << poss << endl;
    cout << "scores: " << sc << endl;
    return 0;
}