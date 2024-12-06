#include <stdlib.h>
#include <time.h>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

void preorderTraverse(TreeNode* root, vector<int>& result) {
    if (!root) {
        return;
    }

    result.push_back(root->val);
    preorderTraverse(root->left, result);
    preorderTraverse(root->right, result);
}

void inorderTraverse(TreeNode* root, vector<int>& result) {
    if (!root) {
        return;
    }

    inorderTraverse(root->left, result);
    result.push_back(root->val);
    inorderTraverse(root->right, result);
}

void postorderTraverse(TreeNode* root, vector<int>& result) {
    if (!root) {
        return;
    }

    postorderTraverse(root->left, result);
    postorderTraverse(root->right, result);
    result.push_back(root->val);
}

void preorderTraverseIterative(TreeNode* root, vector<int>& result) {
    stack<TreeNode*> sk;
    if (root) {
        sk.push(root);
    }

    TreeNode* curr = nullptr;
    while (!sk.empty()) {
        curr = sk.top();
        sk.pop();
        result.push_back(curr->val);
        if (curr->right) {
            sk.push(curr->right);
        }
        if (curr->left) {
            sk.push(curr->left);
        }
    }
}

void inorderTraverseIterative(TreeNode* root, vector<int>& result) {
    TreeNode* curr = root;
    stack<TreeNode*> sk;
    while (curr || !sk.empty()) {
        if (curr) {
            sk.push(curr);
            curr = curr->left;
        } else {
            curr = sk.top();
            sk.pop();
            result.push_back(curr->val);
            curr = curr->right;
        }
    }
}

void postorderTraverseIterative(TreeNode* root, vector<int>& result) {
    TreeNode* curr = root;
    stack<TreeNode*> sk;
    while (curr || !sk.empty()) {
        if (curr) {
            sk.push(curr);
            curr = curr->left;
        } else {
            TreeNode* temp = sk.top()->right;
            if (temp == NULL) {
                temp = sk.top();
                sk.pop();
                result.push_back(temp->val);
                while (!sk.empty() && temp == sk.top()->right) {
                    temp = sk.top();
                    sk.pop();
                    result.push_back(temp->val);
                }
            } else {
                curr = temp;
            }
        }
    }
}

void levelTraverse(TreeNode* root, vector<int>& result) {
    queue<TreeNode*> q;
    if (root) {
        q.push(root);
    }

    TreeNode* curr = nullptr;
    while (!q.empty()) {
        int qLen = q.size();
        for (int i = 0; i < qLen; ++i) {
            curr = q.front();
            q.pop();
            result.push_back(curr->val);
            if (curr->left) {
                q.push(curr->left);
            }
            if (curr->right) {
                q.push(curr->right);
            }
        }
    }
}

class TreeBuilder {
public:
    static TreeNode* buildFromPostorder(vector<int>& postorder, vector<int>& inorder);
    static TreeNode* buildFromPreorder(vector<int>& preorder, vector<int>& inorder);
private:
    static TreeNode* helperPostorder(int inLeft, int inRight, int& postIdx, vector<int>& postorder, vector<int>& inorder, unordered_map<int, int>& inValIdxMap);
    static TreeNode* helperPreorder(int inLeft, int inRight, int& preIdx, vector<int>& preorder, vector<int>& inorder, unordered_map<int, int>& inValIdxMap);
};

TreeNode* TreeBuilder::helperPostorder(int inLeft, int inRight, int& postIdx, vector<int>& postorder, vector<int>& inorder, unordered_map<int, int>& inValIdxMap) {
    if (inLeft > inRight) {
        return nullptr;
    }    
    
    int rootVal = postorder[postIdx--];
    TreeNode* root = new TreeNode(rootVal);
    int inIdx = inValIdxMap[rootVal];
    root->right = helperPostorder(inIdx + 1, inRight, postIdx, postorder, inorder, inValIdxMap);
    root->left = helperPostorder(inLeft, inIdx - 1, postIdx, postorder, inorder, inValIdxMap);
    return root;
}

TreeNode* TreeBuilder::buildFromPostorder(vector<int>& postorder, vector<int>& inorder) {
    unordered_map<int, int> inValIdxMap;
    for (int i = 0; i < inorder.size(); ++i) {
        inValIdxMap[inorder[i]] = i;
    }

    int postIdx = postorder.size() - 1;
    return helperPostorder(0, inorder.size() - 1, postIdx, postorder, inorder, inValIdxMap);
}

TreeNode* TreeBuilder::helperPreorder(int inLeft, int inRight, int& preIdx, vector<int>& preorder, vector<int>& inorder, unordered_map<int, int>& inValIdxMap) {
    if (inLeft > inRight) {
        return nullptr;
    }

    int rootVal = preorder[preIdx++];
    TreeNode* root = new TreeNode(rootVal);
    int inIdx = inValIdxMap[rootVal];
    root->left = helperPreorder(inLeft, inIdx - 1, preIdx, preorder, inorder, inValIdxMap);
    root->right = helperPreorder(inIdx + 1, inRight, preIdx, preorder, inorder, inValIdxMap);
    
    return root;
}

TreeNode* TreeBuilder::buildFromPreorder(vector<int>& preorder, vector<int>& inorder) {
    unordered_map<int, int> inValIdxMap;
    for (int i = 0; i < inorder.size(); ++i) {
        inValIdxMap[inorder[i]] = i;
    }

    int preIdx = 0;
    return helperPreorder(0, inorder.size() - 1, preIdx, preorder, inorder, inValIdxMap);
}

vector<TreeNode*> buildUniqueBST(int start, int end) {
    vector<TreeNode*> result;
    if (start > end) {
        result.push_back(nullptr);
        return result;
    }

    for (int i = start; i <= end; ++i) {
        vector<TreeNode*> leftTrees = buildUniqueBST(start, i - 1);
        vector<TreeNode*> rightTrees = buildUniqueBST(i + 1, end);
        for (auto l : leftTrees) {
            for (auto r : rightTrees) {
                TreeNode* root = new TreeNode(i);
                root->left = l;
                root->right = r;
                result.push_back(root);
            }
        }
    }

    return result;
}

int countUniqueBST(int n) {
    static unordered_map<int, int> cache;
    int cnt = 0;
    
    if (cache.count(n)) {
        return cache[n];
    }

    if (n <= 0) {
        return 1;
    }

    for (int i = 1; i <= n; ++i) {
        int lcnt = countUniqueBST(i - 1);
        int rcnt = countUniqueBST(n - i);
        cnt += lcnt * rcnt;
    }

    cache[n] = cnt;
    return cnt;
}

void testTree() {
    //vector<int> postorder({ 9,15,7,20,3 });
    //vector<int> inorder({ 9,3,15,20,7 });
    //TreeNode* root = TreeBuilder::buildFromPostorder(postorder, inorder);

    vector<int> preorder({ 3, 9, 20, 15, 7 });
    vector<int> inorder({ 9,3,15,20,7 });
    TreeNode* root = TreeBuilder::buildFromPreorder(preorder, inorder);

    vector<int> result;
    levelTraverse(root, result);
    for (auto i : result) {
        printf("%d ", i);
    }
    printf("\n");
}
