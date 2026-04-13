// File: Project2_BST.cpp
// Name: Drew Whiting
// Date: 04/02/2026
// Course: COP3415.02I&T

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE *outfile;

//  CLASS DEFINITIONS

// itemNode: represents one item inside a named tree (blue nodes in diagram)
class itemNode
{
public:
    char name[50];
    int count;
    itemNode *left, *right;

    // Default constructor
    itemNode()
    {
        name[0] = '\0';
        count = 0;
        left = NULL;
        right = NULL;
    }

    // Parameterized constructor
    itemNode(char itemName[], int population)
    {
        strcpy(name, itemName);
        count = population;
        left = NULL;
        right = NULL;
    }
};

// treeNameNode: represents one named tree in the Name BST (black nodes in diagram)
class treeNameNode
{
public:
    char treeName[50];
    treeNameNode *left, *right;
    itemNode *theTree; 

    // Default constructor
    treeNameNode()
    {
        treeName[0] = '\0';
        theTree = NULL;
        left = NULL;
        right = NULL;
    }

    // Parameterized constructor
    treeNameNode(char name[])
    {
        strcpy(treeName, name);
        theTree = NULL;
        left = NULL;
        right = NULL;
    }
};


//  ITEM TREE FUNCTIONS


/*
 * Function: insertItem
 * Description: Inserts a new itemNode into an Item BST using alphabetical
 *              order (strcmp) on the item name as the BST key.
 * Parameters:
 *   root      - pointer to the root of the Item BST
 *   itemName  - name of the item to insert
 *   count     - count of that item
 * Returns: pointer to the root of the Item BST
 */
itemNode* insertItem(itemNode *root, char itemName[], int count)
{
    // Base case: empty spot found, create and return new node
    if (root == NULL)
    {
        return new itemNode(itemName, count);
    }

    // Decide left or right using strcmp
    if (strcmp(itemName, root->name) < 0)
    {
        root->left = insertItem(root->left, itemName, count);
    }
    else
    {
        root->right = insertItem(root->right, itemName, count);
    }

    return root;
}

/*
 * Function: searchItem
 * Description: Searches for an item by name in an Item BST.
 * Parameters:
 *   root     - root of the Item BST to search
 *   itemName - name to look for
 * Returns: pointer to the found itemNode, or NULL if not found
 */
itemNode* searchItem(itemNode *root, char itemName[])
{
    // Base case: not found
    if (root == NULL) return NULL;

    int cmp = strcmp(itemName, root->name);

    if (cmp == 0)       return root;
    else if (cmp < 0)   return searchItem(root->left, itemName);
    else                return searchItem(root->right, itemName);
}

/*
 * Function: countBefore
 * Description: Counts how many items in the Item BST come BEFORE a given
 *              item name alphabetically
 *              Uses BST inorder logic: everything in left subtree of a node
 *              with name < target also counts.
 * Parameters:
 *   root       - root of the Item BST
 *   targetName - the item name we are comparing against
 * Returns: integer count of items alphabetically before targetName
 */
int countBefore(itemNode *root, char targetName[])
{
    if (root == NULL) return 0;

    int cmp = strcmp(root->name, targetName);

    if (cmp < 0)
    {
       
        int leftCount = countBefore(root->left, targetName);
        return leftCount + 1 + countBefore(root->right, targetName);
    }
    else
    {
        return countBefore(root->left, targetName);
    }
}

/*
 * Function: getHeight
 * Description: Computes the height of a BST. A single node = height 1,
 *              empty tree = height 0
 * Parameters:
 *   root - root of the Item BST
 * Returns: integer height
 */
int getHeight(itemNode *root)
{
    if (root == NULL) return 0;

    int leftH  = getHeight(root->left);
    int rightH = getHeight(root->right);

    // Height = 1 + max of children heights
    return 1 + (leftH > rightH ? leftH : rightH);
}

/*
 * Function: sumCounts
 * Description: Sums up the count values of all items in an Item BST.
 *              Used by the "count" query.
 * Parameters:
 *   root - root of the Item BST
 * Returns: integer sum of all item counts
 */
int sumCounts(itemNode *root)
{
    if (root == NULL) return 0;
    return root->count + sumCounts(root->left) + sumCounts(root->right);
}

/*
 * Function: printItemInorder
 * Description: Prints item names in alphabetical order.
 *              Prints to both console and outfile.
 * Parameters:
 *   root - root of the Item BST
 * Returns: void
 */
void printItemInorder(itemNode *root)
{
    if (root == NULL) return;
    printItemInorder(root->left);
    printf("%s ", root->name);
    fprintf(outfile, "%s ", root->name);
    printItemInorder(root->right);
}

//  NAME TREE FUNCTIONS

/*
 * Function: insertNameNode
 * Description: Inserts a new treeNameNode into the Name BST using
 *              alphabetical order on treeName as the key.
 * Parameters:
 *   root     - pointer to root of Name BST
 *   treeName - name string for the new tree
 * Returns: pointer to root of Name BST
 */
treeNameNode* insertNameNode(treeNameNode *root, char treeName[])
{
    // Base case: insert here
    if (root == NULL)
    {
        return new treeNameNode(treeName);
    }

    if (strcmp(treeName, root->treeName) < 0)
    {
        root->left = insertNameNode(root->left, treeName);
    }
    else
    {
        root->right = insertNameNode(root->right, treeName);
    }

    return root;
}

/*
 * Function: buildNameTree
 * Description: Reads N tree names from the input file and inserts each
 *              into the Name BST. Returns the root of the Name BST.
 * Parameters:
 *   infile - FILE pointer to the open input file
 *   N      - number of tree names to read
 * Returns: pointer to root of the completed Name BST
 */
treeNameNode* buildNameTree(FILE *infile, int N)
{
    treeNameNode *root = NULL;
    char name[50];

    for (int i = 0; i < N; i++)
    {
        // Read one tree name from file
        fscanf(infile, "%s", name);
        // Insert into Name BST
        root = insertNameNode(root, name);
    }

    return root;
}

/*
 * Function: searchNameNode
 * Description: Searches the Name BST for a node with a given tree name.
 * Parameters:
 *   root     - root of Name BST
 *   treeName - name to search for (char array, size 50)
 * Returns: pointer to found treeNameNode, or NULL if not found
 */
treeNameNode* searchNameNode(treeNameNode *root, char treeName[50])
{
    if (root == NULL) return NULL;

    int cmp = strcmp(treeName, root->treeName);

    if (cmp == 0)       return root;
    else if (cmp < 0)   return searchNameNode(root->left, treeName);
    else                return searchNameNode(root->right, treeName);
}

/*
 * Function: printNameInorder
 * Description: Prints all tree names in the Name BST in alphabetical order.
 *              Used in traverse_in_traverse for the first line of output.
 * Parameters:
 *   root - root of Name BST
 * Returns: void
 */
void printNameInorder(treeNameNode *root)
{
    if (root == NULL) return;
    printNameInorder(root->left);
    printf("%s ", root->treeName);
    fprintf(outfile, "%s ", root->treeName);
    printNameInorder(root->right);
}

/*
 * Function: traverse_in_traverse
 * Description: Performs an inorder traversal of the Name BST. For each
 *              name node visited, it prints the name as a header and then
 *              prints that name's Item BST in inorder. This produces the
 *              full output block shown in the sample output.
 * Parameters:
 *   root - root of the Name BST
 * Returns: void
 */
void traverse_in_traverse(treeNameNode *root)
{
    if (root == NULL) return;

    // Inorder: left, process current, right
    traverse_in_traverse(root->left);

    // Print header for this tree's name
    printf("\n***%s***\n", root->treeName);
    fprintf(outfile, "\n***%s***\n", root->treeName);

    // Print this tree's items in alphabetical order
    printItemInorder(root->theTree);

    // Move to next line after items
    printf("\n");
    fprintf(outfile, "\n");

    traverse_in_traverse(root->right);
}

//  QUERY HANDLER FUNCTIONS

/*
 * Function: handleSearch
 * Description: Handles the "search" query. First finds the named tree in
 *              the Name BST. Then searches for the item in that tree's
 *              Item BST. Prints result to console and outfile.
 * Parameters:
 *   nameRoot - root of the Name BST
 *   treeName - which tree to search in
 *   itemName - what item to look for
 * Returns: void
 */
void handleSearch(treeNameNode *nameRoot, char treeName[], char itemName[])
{
    // Step 1: Find the tree in the Name BST
    treeNameNode *treeNode = searchNameNode(nameRoot, treeName);

    if (treeNode == NULL)
    {
        // Tree doesn't exist at all
        printf("%s does not exist\n", treeName);
        fprintf(outfile, "%s does not exist\n", treeName);
        return;
    }

    // Step 2: Search for item inside that tree's Item BST
    itemNode *found = searchItem(treeNode->theTree, itemName);

    if (found == NULL)
    {
        printf("%s not found in %s\n", itemName, treeName);
        fprintf(outfile, "%s not found in %s\n", itemName, treeName);
    }
    else
    {
        printf("%d %s found in %s\n", found->count, itemName, treeName);
        fprintf(outfile, "%d %s found in %s\n", found->count, itemName, treeName);
    }
}

/*
 * Function: handleItemBefore
 * Description: Handles the "item_before" query. Finds the named tree, then
 *              counts how many items in that tree are alphabetically before
 *              the given item name.
 * Parameters:
 *   nameRoot - root of the Name BST
 *   treeName - which tree to operate on
 *   itemName - the reference item name
 * Returns: void
 */
void handleItemBefore(treeNameNode *nameRoot, char treeName[], char itemName[])
{
    treeNameNode *treeNode = searchNameNode(nameRoot, treeName);

    if (treeNode == NULL)
    {
        printf("%s does not exist\n", treeName);
        fprintf(outfile, "%s does not exist\n", treeName);
        return;
    }

    int before = countBefore(treeNode->theTree, itemName);
    printf("item before %s: %d\n", itemName, before);
    fprintf(outfile, "item before %s: %d\n", itemName, before);
}

/*
 * Function: handleHeightBalance
 * Description: Handles the "height_balance" query. Finds the named tree,
 *              computes left and right subtree heights of the Item BST root,
 *              determines if the tree is balanced (|diff| <= 1).
 * Parameters:
 *   nameRoot - root of the Name BST
 *   treeName - which tree to check
 * Returns: void
 */
void handleHeightBalance(treeNameNode *nameRoot, char treeName[])
{
    treeNameNode *treeNode = searchNameNode(nameRoot, treeName);

    if (treeNode == NULL)
    {
        printf("%s does not exist\n", treeName);
        fprintf(outfile, "%s does not exist\n", treeName);
        return;
    }

    // Get heights of left and right subtrees of the Item BST's root
    int leftH  = getHeight(treeNode->theTree ? treeNode->theTree->left  : NULL);
    int rightH = getHeight(treeNode->theTree ? treeNode->theTree->right : NULL);
    int diff   = leftH - rightH;
    if (diff < 0) diff = -diff; // absolute value

    if (diff > 1)
    {
        printf("%s: left height %d, right height %d, difference %d, not balanced\n",
               treeName, leftH, rightH, diff);
        fprintf(outfile, "%s: left height %d, right height %d, difference %d, not balanced\n",
                treeName, leftH, rightH, diff);
    }
    else
    {
        printf("%s: left height %d, right height %d, difference %d, balanced\n",
               treeName, leftH, rightH, diff);
        fprintf(outfile, "%s: left height %d, right height %d, difference %d, balanced\n",
                treeName, leftH, rightH, diff);
    }
}

/*
 * Function: handleCount
 * Description: Handles the "count" query. Finds the named tree and sums
 *              up all item counts in its Item BST.
 * Parameters:
 *   nameRoot - root of the Name BST
 *   treeName - which tree to count
 * Returns: void
 */
void handleCount(treeNameNode *nameRoot, char treeName[])
{
    treeNameNode *treeNode = searchNameNode(nameRoot, treeName);

    if (treeNode == NULL)
    {
        printf("%s does not exist\n", treeName);
        fprintf(outfile, "%s does not exist\n", treeName);
        return;
    }

    int total = sumCounts(treeNode->theTree);
    printf("%s count %d\n", treeName, total);
    fprintf(outfile, "%s count %d\n", treeName, total);
}

//  MAIN FUNCTION

/*
 * Function: main
 * Description: Entry point. Opens in.txt and out.txt, reads N/I/Q,
 *              builds the Name BST, inserts all items into their trees,
 *              prints the inorder traversal, then processes Q queries.
 * Parameters: none (standard main)
 * Returns: 0 on success
 */
int main()
{
    // Open input and output files
    FILE *infile = fopen("in.txt", "r");
    outfile = fopen("out.txt", "w");

    if (infile == NULL)
    {
        printf("Error: could not open in.txt\n");
        return 1;
    }
    if (outfile == NULL)
    {
        printf("Error: could not open out.txt\n");
        return 1;
    }

    // Read N, I, Q from first line
    int N, I, Q;
    fscanf(infile, "%d %d %d", &N, &I, &Q);

    // Build the Name Tree (Step 1)
    // Reads the next N lines, each containing one tree name
    treeNameNode *nameRoot = buildNameTree(infile, N);

    // Insert Items into Their Trees (Step 2)
    // Each of the next I lines: "treeName itemName count"
    for (int i = 0; i < I; i++)
    {
        char treeName[50], itemName[50];
        int  count;

        fscanf(infile, "%s %s %d", treeName, itemName, &count);

        // Find the correct name node in the Name BST
        treeNameNode *targetTree = searchNameNode(nameRoot, treeName);

        if (targetTree != NULL)
        {
            // Insert item into that tree's Item BST
            targetTree->theTree = insertItem(targetTree->theTree, itemName, count);
        }
    }

    // Print Name Tree Inorder, then each Item Tree Inorder 
    // First line: all tree names in alphabetical order
    printNameInorder(nameRoot);
    printf("\n");
    fprintf(outfile, "\n");

    // Then for each name (inorder), print its items
    traverse_in_traverse(nameRoot);

    // Process Q Queries
    for (int q = 0; q < Q; q++)
    {
        char command[50];
        fscanf(infile, "%s", command);

        if (strcmp(command, "search") == 0)
        {
            char treeName[50], itemName[50];
            fscanf(infile, "%s %s", treeName, itemName);
            handleSearch(nameRoot, treeName, itemName);
        }
        else if (strcmp(command, "item_before") == 0)
        {
            char treeName[50], itemName[50];
            fscanf(infile, "%s %s", treeName, itemName);
            handleItemBefore(nameRoot, treeName, itemName);
        }
        else if (strcmp(command, "height_balance") == 0)
        {
            char treeName[50];
            fscanf(infile, "%s", treeName);
            handleHeightBalance(nameRoot, treeName);
        }
        else if (strcmp(command, "count") == 0)
        {
            char treeName[50];
            fscanf(infile, "%s", treeName);
            handleCount(nameRoot, treeName);
        }
    }

    // Close files
    fclose(infile);
    fclose(outfile);

    return 0;
}