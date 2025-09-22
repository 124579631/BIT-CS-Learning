#include <iostream>
#include <string>
using namespace std;

int main() {
    int T;
    string target = "fattyhappy";
    int target_len = target.length();
    cin >> T;
    
    while (T--)
    {
        string s;
        cin >> s;
        int n = s.length();

        if (n < target_len)
        {
            cout << -1 << endl;
            continue;
        }
        
        bool has_existing = false;
        for (int i = 0; i <= n - target_len; i++)
        {
            if (s.substr(i, target_len) == target)
            {
                has_existing = true;
                break;
            }
        }
        
        if (has_existing) {
            bool found = false;
            for (int i = 0; i < n && !found; i++)
            {
                for (int j = i + 1; j < n; j++)
                {
                    if (s[i] == s[j])
                    {
                        cout << i + 1 << " " << j + 1 << endl;
                        found = true;
                        break;
                    }
                }
            }
            if (!found)
            {
                cout << -1 << endl;
            }
            continue;
        }
        
        bool solution_found = false;
        
        for (int start = 0; start <= n - target_len; start++)
        {
            int diff_count = 0;
            int diff_positions[2] = {-1, -1};
            
            for (int j = 0; j < target_len; j++)
            {
                if (s[start + j] != target[j])
                {
                    if (diff_count < 2)
                    {
                        diff_positions[diff_count] = j;
                    }
                    diff_count++;
                    if (diff_count > 2) break;
                }
            }
            
            if (diff_count > 2) continue;
            
            if (diff_count == 0)
            {
                continue;
            }
            else if (diff_count == 1)
            {
                int wrong_pos = start + diff_positions[0];
                char needed_char = target[diff_positions[0]];
                
                for (int k = 0; k < n; k++)
                {
                    if (k < start || k >= start + target_len)
                    {
                        if (s[k] == needed_char)
                        {
                            cout << wrong_pos + 1 << " " << k + 1 << endl;
                            solution_found = true;
                            break;
                        }
                    }
                }
                if (solution_found) break;
            }
            else if (diff_count == 2)
            {
                int pos1 = start + diff_positions[0];
                int pos2 = start + diff_positions[1];
                if (s[pos1] == target[diff_positions[1]] && s[pos2] == target[diff_positions[0]])
                {
                    cout << pos1 + 1 << " " << pos2 + 1 << endl;
                    solution_found = true;
                    break;
                }
            }
        }
        
        if (!solution_found)
        {
            cout << -1 << endl;
        }
    }
    
    return 0;
}
