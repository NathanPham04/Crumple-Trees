#include "catch_amalgamated.hpp"
#include "CrumpleTree.hpp"

#include <fstream>
#include <string>
#include <sstream>
#include <vector>


namespace{




/* Remember, these are prerequisites to having us grade
    the related part of the assignment.  These are not
    worth points on their own, nor are they comprehensive.

    REMEMBER TO TEST YOUR OWN CODE COMPREHENSIVELY. 

*/

TEST_CASE("FindTheRoot", "[RequiredBasicFunctionality]")
{
    CrumpleTree<int, std::string> tree;
    tree.insert(5, "foo");

    REQUIRE( tree.contains(5) );
}

TEST_CASE("FindOneHop", "[RequiredBasicFunctionality]")
{
    CrumpleTree<int, std::string> tree;
    tree.insert(5, "foo");
    tree.insert(10, "bar");

    REQUIRE( tree.contains(10) );
}

TEST_CASE("FindTwoHops", "[RequiredBasicFunctionality]")
{
    CrumpleTree<int, std::string> tree;
    tree.insert(5, "foo");
    tree.insert(3, "sna");
    tree.insert(10, "bar");
    tree.insert(12, "twelve");

    REQUIRE( tree.contains(12) );
}



TEST_CASE("CanAddAFew", "[RequiredBasicFunctionality]")
{
    CrumpleTree<int, std::string> tree;
    tree.insert(5, "foo");
    tree.insert(3, "sna");
    tree.insert(10, "bar");
    tree.insert(12, "twelve");
    tree.insert(15, "fifteen");

    REQUIRE( tree.size() == 5 );
}


TEST_CASE("DoAPostOrder", "[RequiredBasicFunctionality]")
{
    CrumpleTree<int, std::string> tree;
    tree.insert(5, "foo");
    tree.insert(3, "sna");
    tree.insert(10, "bar");
    auto trav = tree.postOrder();
    std::vector<int> expected = {3, 10, 5};
    REQUIRE(trav == expected);

}



TEST_CASE("RemoveDoesARemove", "[RequiredCrumpleTree]")
{
    CrumpleTree<int, std::string> tree;
    tree.insert(20, "are");
    tree.insert(19, "you");
    tree.insert(18, "following");
    tree.insert(12, "from");
    tree.insert(9, "lecture?");
    REQUIRE( tree.contains( 20 ) );
    REQUIRE( tree.contains( 19 ) );
    REQUIRE( tree.contains( 18 ) );
    REQUIRE( tree.contains( 12 ) );
    REQUIRE( tree.contains( 9 ) );
    tree.remove(9);
    tree.remove(18);
    // What happens?  12 is now a leaf and must fall.  But 19 is a (2,2) and remains at level 3.
    REQUIRE( ! tree.contains(9));
    REQUIRE( ! tree.contains(18));
    REQUIRE( tree.getLevel(20) == 1);
    REQUIRE( tree.getLevel(12) == 1);
    REQUIRE( tree.getLevel(19) == 3);

}

// ------------------------------------------------------------------------------------------------------------

TEST_CASE("NodeFunctionality", "[Helper]")
{
    Node<unsigned, unsigned>* tmp = new Node<unsigned, unsigned>(1,2,2);
    REQUIRE( tmp->key == 1 );
    REQUIRE( tmp->val == 2 );
    REQUIRE( tmp->level == 2 );
    REQUIRE( tmp->parent == nullptr );
    REQUIRE( tmp->left == nullptr );
    REQUIRE( tmp->right == nullptr );

    Node<unsigned, unsigned>* left = new Node<unsigned, unsigned>(3,4,1,tmp);
    REQUIRE( left->key == 3 );
    REQUIRE( left->val == 4 );
    REQUIRE( left->level == 1 );
    REQUIRE( left->parent == tmp );
    REQUIRE( left->left == nullptr );
    REQUIRE( left->right == nullptr );

    tmp->left = left;
    REQUIRE( tmp->left->key == 3 );

    Node<unsigned, unsigned>* right = new Node<unsigned, unsigned>(5,10,1,tmp);
    REQUIRE( right->key == 5 );
    REQUIRE( right->val == 10 );
    REQUIRE( right->level == 1 );
    REQUIRE( right->parent == tmp );
    REQUIRE( right->left == nullptr );
    REQUIRE( right->right == nullptr );

    tmp->right = right;
    REQUIRE( tmp->right->key == 5 );

    delete tmp;
    delete left;
    delete right;

    Node<std::string, unsigned> str("nathan", 1, 1);
    REQUIRE( str.parent == nullptr );
    REQUIRE( str.left == nullptr );
    REQUIRE( str.right == nullptr );
    REQUIRE( str.level == 1 );
    REQUIRE( str.key == "nathan" );
    REQUIRE( str.val == 1 );

    Node<std::string, std::string> strstr("bal", "bol", 1);
    REQUIRE( strstr.parent == nullptr );
    REQUIRE( strstr.left == nullptr );
    REQUIRE( strstr.right == nullptr );
    REQUIRE( strstr.level == 1 );
    REQUIRE( strstr.key == "bal" );
    REQUIRE( strstr.val == "bol" );

    Node<unsigned, std::string> intstr(90, "bol", 1);
    REQUIRE( intstr.parent == nullptr );
    REQUIRE( intstr.left == nullptr );
    REQUIRE( intstr.right == nullptr );
    REQUIRE( intstr.level == 1 );
    REQUIRE( intstr.key == 90 );
    REQUIRE( intstr.val == "bol" );
}

TEST_CASE("EmptyCrumpleTree", "[Actual]")
{
    CrumpleTree<unsigned, unsigned> tmp1;
    REQUIRE( tmp1.size() == 0 );
    REQUIRE( tmp1.isEmpty() == true );

    CrumpleTree<unsigned, std::string> tmp2;
    REQUIRE( tmp2.size() == 0 );
    REQUIRE( tmp2.isEmpty() == true );

    CrumpleTree<std::string, std::string> tmp3;
    REQUIRE( tmp3.size() == 0 );
    REQUIRE( tmp3.isEmpty() == true );

    CrumpleTree<std::string, unsigned> tmp4;
    REQUIRE( tmp4.size() == 0 );
    REQUIRE( tmp4.isEmpty() == true );
}

TEST_CASE("findKeyHelper", "[Helper]")
{
    Node<unsigned, unsigned>* root = nullptr;
    unsigned key = 0;
    REQUIRE( findKeyHelper(root, key) == nullptr );

    root = new Node<unsigned, unsigned>(5,1,2);                                             // 5
    Node<unsigned, unsigned>* shouldBeRoot = findKeyHelper(root, key);
    REQUIRE( shouldBeRoot == root );

    Node<unsigned, unsigned>* leftChild = new Node<unsigned, unsigned>(4,0,1,root);         //      5
    root->left = leftChild;                                                                 //    4
    REQUIRE( findKeyHelper(root, key) == leftChild );
    unsigned smallKey = 3;
    REQUIRE( findKeyHelper(root, smallKey) == leftChild );

    Node<unsigned, unsigned>* rightChild = new Node<unsigned, unsigned>(100,0,1,root);      //      5
    root->right = rightChild;                                                               //    4   100
    unsigned bigKey = 6;
    REQUIRE( findKeyHelper(root, bigKey) == rightChild );
    unsigned biggestKey = 10000000;
    REQUIRE( findKeyHelper(root, biggestKey) == rightChild );

    unsigned five = 5;
    unsigned four = 4;
    unsigned hundred = 100;

    REQUIRE( findKeyHelper(root, five) == root );
    REQUIRE( findKeyHelper(root, four) == leftChild );
    REQUIRE( findKeyHelper(root, hundred) == rightChild );

    delete root;
    delete leftChild;
    delete rightChild;
}

TEST_CASE("insertBST", "[Actual]")
{
    CrumpleTree<unsigned, unsigned> t1;
    REQUIRE( t1.contains(5) == false );
    REQUIRE( t1.size() == 0 );
    REQUIRE( t1.isEmpty() == true );
    t1.insert(5, 6);
    REQUIRE( t1.contains(5) == true );
    REQUIRE( t1.size() == 1 );
    REQUIRE( t1.isEmpty() == false );
    t1.insert(3, 10);
    t1.insert(1, 1);
    t1.insert(4, 4);
    t1.insert(5, 1);
    t1.insert(3, 1);
    t1.insert(4, 1);
    t1.insert(1, 1);
    REQUIRE( t1.size() == 4 );
    t1.insert(10, 10);
    t1.insert(8,8);
    t1.insert(9,9);
    REQUIRE( t1.size() == 7 );
    REQUIRE( t1.contains(13) == false );
    REQUIRE( t1.contains(5) == true );
    REQUIRE( t1.contains(3) == true );
    REQUIRE( t1.contains(1) == true );
    REQUIRE( t1.contains(4) == true );
    REQUIRE( t1.contains(10) == true );
    REQUIRE( t1.contains(8) == true );
    REQUIRE( t1.contains(9) == true );
    std::vector<unsigned> t1exp = {1,3,4,5,8,9,10};
    REQUIRE( t1.inOrder() == t1exp );

    CrumpleTree<unsigned, std::string> t2;
    t2.insert(4, "hello");
    t2.insert(2, "hello");
    t2.insert(3, "hello");
    REQUIRE( t2.size() == 3 );
    REQUIRE( t2.isEmpty() == false );
    REQUIRE( t2.contains(4) == true );
    REQUIRE( t2.contains(3) == true );
    REQUIRE( t2.contains(2) == true );
    REQUIRE( t2.contains(5) == false );
    std::vector<unsigned> t2exp = {2,3,4};
    REQUIRE( t2.inOrder() == t2exp );

    CrumpleTree<std::string, unsigned> t3;
    t3.insert("n", 1);
    t3.insert("g", 1);
    t3.insert("z", 1);
    t3.insert("g", 6);
    REQUIRE( t3.size() == 3 );
    REQUIRE( t3.isEmpty() == false );
    REQUIRE( t3.contains("n") == true );
    REQUIRE( t3.contains("g") == true );
    REQUIRE( t3.contains("z") == true );
    REQUIRE( t3.contains("m") == false );
    std::vector<std::string> t3exp = {"g","n","z"};
    REQUIRE( t3.inOrder() == t3exp );

    CrumpleTree<std::string, std::string> t4;
    t4.insert("nathan", "a");
    t4.insert("natahan", "b");
    t4.insert("zathan", "c");
    t4.insert("a", "d");
    t4.insert("a", "blah");
    REQUIRE( t4.size() == 4 ); 
    REQUIRE( t4.isEmpty() == false ); 
    REQUIRE( t4.contains("aksdfj") == false ); 
    REQUIRE( t4.contains("nathan") == true ); 
    REQUIRE( t4.contains("zathan") == true ); 
    REQUIRE( t4.contains("natahan") == true ); 
    REQUIRE( t4.contains("a") == true ); 
    std::vector<std::string> t4exp = {"a","natahan","nathan","zathan"};
    REQUIRE( t4.inOrder() == t4exp );
}

TEST_CASE("normalFind", "[Actual]")
{
    CrumpleTree<unsigned, unsigned> k1;
    REQUIRE_THROWS_AS( k1.find(10), ElementNotFoundException );
    k1.insert(10,10);
    k1.insert(5,5);
    k1.insert(15,15);
    unsigned& val = k1.find(10);
    REQUIRE( val == 10 );
    val = 100;
    REQUIRE( k1.find(10) == 100 );
    unsigned& val2 = k1.find(5);
    val2 = 10;
    REQUIRE( k1.find(5) == 10 );
    REQUIRE( k1.find(15) == 15 );

    CrumpleTree<unsigned, std::string> k2;
    REQUIRE_THROWS_AS( k2.find(10), ElementNotFoundException );
    k2.insert(5, "hello");
    REQUIRE( k2.find(5) == "hello" );
    std::string& val3 = k2.find(5);
    val3 = "nathan";
    REQUIRE( k2.find(5) == "nathan" );
    val3 = "boy";
    REQUIRE( k2.find(5) == "boy" );

    CrumpleTree<std::string, unsigned> k3;
    REQUIRE_THROWS_AS( k3.find("nathan"), ElementNotFoundException );
    k3.insert("nathan", 5);
    k3.insert("bruh", 10);
    REQUIRE( k3.find("nathan") == 5 );
    REQUIRE( k3.find("bruh") == 10 );
    unsigned& val4 = k3.find("nathan");
    val4 = 1000000;
    unsigned& val5 = k3.find("bruh");
    val5 = 0;
    REQUIRE( k3.find("nathan") == 1000000 );
    REQUIRE( k3.find("bruh") == 0 );

    CrumpleTree<std::string, std::string> k4;
    REQUIRE_THROWS_AS( k4.find("nathan"), ElementNotFoundException );
    k4.insert("lemon", "car");
    REQUIRE( k4.find("lemon") == "car" );
    std::string& val6 = k4.find("lemon");
    val6 = "notcar";
    REQUIRE( k4.find("lemon") == "notcar" );

}
                        
TEST_CASE("constFind", "[Actual]")
{
    CrumpleTree<unsigned, unsigned> k1;
    k1.insert(1,1);
    const CrumpleTree<unsigned, unsigned>& k1Cpy = k1;
    REQUIRE_THROWS_AS( k1Cpy.find(0), ElementNotFoundException );
    REQUIRE( k1Cpy.find(1) == 1 );

    CrumpleTree<unsigned, std::string> k2;
    k2.insert(1,"nathan");
    const CrumpleTree<unsigned, std::string>& k2Cpy = k2;
    REQUIRE_THROWS_AS( k2Cpy.find(0), ElementNotFoundException );
    REQUIRE( k2Cpy.find(1) == "nathan" );
    
    CrumpleTree<std::string, unsigned> k3;
    k3.insert("nathan",1);
    const CrumpleTree<std::string, unsigned>& k3Cpy = k3;
    REQUIRE_THROWS_AS( k3Cpy.find(""), ElementNotFoundException );
    REQUIRE( k3Cpy.find("nathan") == 1 );
    
    CrumpleTree<std::string, std::string> k4;
    k4.insert("nathan","pham");
    const CrumpleTree<std::string, std::string>& k4Cpy = k4;
    REQUIRE_THROWS_AS( k4Cpy.find(""), ElementNotFoundException );
    REQUIRE( k4Cpy.find("nathan") == "pham" );
}

TEST_CASE("inOrder", "[Actual]")
{
    CrumpleTree<unsigned, unsigned> k1;
    std::vector<unsigned> k1out = k1.inOrder();
    std::vector<unsigned> expected1 = {};
    REQUIRE( k1out == expected1 );
    k1.insert(10,10);
    k1.insert(3,3);
    k1.insert(15,15);
    k1.insert(17,17);
    k1.insert(13,13);
    k1.insert(7,7);
    k1.insert(0,0);
    k1.insert(2, 2);
    k1out = k1.inOrder();
    expected1 = {0,2,3,7,10,13,15,17};
    REQUIRE( k1out == expected1 );

    CrumpleTree<unsigned, std::string> k2;
    std::vector<unsigned> k2out = k2.inOrder();
    std::vector<unsigned> expected2 = {};
    REQUIRE( k2out == expected2 );
    k2.insert(100, "");
    k2.insert(1435, "");
    k2.insert(14, "");
    k2.insert(114, "");
    k2.insert(20, "");
    k2.insert(830, "");
    k2.insert(19, "");
    k2out = k2.inOrder();
    expected2 = {14,19,20,100,114,830,1435};
    REQUIRE( k2out == expected2 );

    CrumpleTree<std::string, unsigned> k3;
    k3.insert("nathan", 5);
    std::vector<std::string> k3out = k3.inOrder();
    std::vector<std::string> expected3 = {"nathan"};
    REQUIRE( k3out == expected3 );
    k3.insert("z", 0);
    k3out = k3.inOrder();
    expected3 = {"nathan", "z"};
    REQUIRE( k3out == expected3 );

    CrumpleTree<std::string, std::string> k4;
    k4.insert("blah", "na");
    k4.insert("a","a");
    k4.insert("ab", "ab");
    std::vector<std::string> k4out = k4.inOrder();
    std::vector<std::string> expected4 = {"a", "ab", "blah"};
    REQUIRE( k4out == expected4 );

}

TEST_CASE("preOrder", "[Actual]")
{
    CrumpleTree<unsigned, unsigned> k1;
    std::vector<unsigned> k1out = k1.preOrder();
    std::vector<unsigned> expected1 = {};
    REQUIRE( k1out == expected1 );
    k1.insert(3,3);
    k1.insert(2,2);
    k1.insert(1,1);
    k1out = k1.preOrder();
    expected1 = {2,1,3};
    REQUIRE( k1out == expected1 );

    CrumpleTree<unsigned, std::string> k2;
    k2.insert(5,"");
    k2.insert(3,"");
    k2.insert(4,"");
    k2.insert(2,"");
    k2.insert(1,"");
    std::vector<unsigned> k2out = k2.preOrder();
    std::vector<unsigned> expected2 = {4,2,1,3,5};
    REQUIRE( k2out == expected2 );

    CrumpleTree<std::string, unsigned> k3;
    k3.insert("n",1);
    k3.insert("p",1);
    k3.insert("z",1);
    k3.insert("a",1);
    std::vector<std::string> k3out = k3.preOrder();
    std::vector<std::string> expected3 = {"p","n","a","z"};
    REQUIRE( k3out == expected3 );

    CrumpleTree<std::string, std::string> k4;
    k4.insert("m","");
    k4.insert("b","");
    k4.insert("d","");
    std::vector<std::string> k4out = k4.preOrder();
    std::vector<std::string> expected4 = {"d","b","m"};
    REQUIRE( k4out == expected4 );
}

TEST_CASE("postOrder", "[Actual]")
{
    CrumpleTree<unsigned, unsigned> k1;
    std::vector<unsigned> k1out = k1.postOrder();
    std::vector<unsigned> expected1 = {};
    REQUIRE( k1out == expected1 );
    k1.insert(5,5);                             //       5
    k1.insert(3,3);                             //     3 
    k1.insert(2,2);                             //    2  4
    k1.insert(4,4);
    k1out = k1.postOrder();
    expected1 = {2,4,5,3};
    REQUIRE( k1out == expected1 );

    CrumpleTree<unsigned, std::string> k2;
    k2.insert(5,"");
    k2.insert(10,"");
    k2.insert(12,"");
    std::vector<unsigned> k2out = k2.postOrder();
    std::vector<unsigned> expected2 = {5,12,10};
    REQUIRE( k2out == expected2 );

    CrumpleTree<std::string, unsigned> k3;
    k3.insert("nathan",0);
    k3.insert("bab",0);
    k3.insert("ksdf",0);
    k3.insert("nvls",0);
    std::vector<std::string> k3out = k3.postOrder();
    std::vector<std::string> expected3 = {"bab","nvls","nathan","ksdf"};
    REQUIRE( k3out == expected3 );

    CrumpleTree<std::string, std::string> k4;
    k4.insert("kasdf","");
    k4.insert("adfasd","");
    k4.insert("rl2r","");
    k4.insert("kasdf","");
    k4.insert("vxcv","");
    std::vector<std::string> k4out = k4.postOrder();
    std::vector<std::string> expected4 = {"adfasd","vxcv","rl2r","kasdf"};
    REQUIRE( k4out == expected4 );
}

TEST_CASE("isLeafNode", "[Helper]")
{
    Node<unsigned, unsigned>* k1 = new Node<unsigned, unsigned>(1,1,1);
    REQUIRE( isLeafNode(k1) == true );
    Node<unsigned, unsigned>* k2 = new Node<unsigned, unsigned>(2,2,2,k1);
    k1->left = k2;
    REQUIRE( isLeafNode(k1) == false );
    REQUIRE( isLeafNode(k2) == true );

    postOrderDelete(k1);
}

TEST_CASE("getPredecessor", "[Helper]")
{
    CrumpleTree<unsigned, unsigned> k1;
    std::vector<unsigned> tmp = {20,19,18,12,9,17,7,5,13,15,6,16,14};
    for(auto num: tmp)
    {
        k1.insert(num, num);
    }
    REQUIRE( getPredecessor(k1.testFindKey(12))->key == 9 );

    CrumpleTree<unsigned, std::string> k2;
    std::vector<unsigned> tmp2 = {20,19,18,12,9,17,7,5,13,15,6,16,14};
    for(auto num: tmp2)
    {
        k2.insert(num, "num");
    }
    REQUIRE( getPredecessor(k1.testFindKey(18))->key == 17 );

    CrumpleTree<std::string, std::string> k3;
    std::vector<std::string> tmp3 = {"t","s","r","l","i","q","g","e","m","o","f","p","n"};
    for(auto word: tmp3)
    {
        k3.insert(word, "num");
    }
    REQUIRE( getPredecessor(k3.testFindKey("l"))->key == "i" );

    CrumpleTree<std::string, unsigned> k4;
    std::vector<std::string> tmp4 = {"t","s","r","l","i","q","g","e","m","o","f","p","n"};
    for(auto word: tmp4)
    {
        k4.insert(word, 0);
    }
    REQUIRE( getPredecessor(k4.testFindKey("o"))->key == "n" );
}

TEST_CASE("getSuccessor", "[Helper]")
{
    CrumpleTree<unsigned, unsigned> k1;
    std::vector<unsigned> tmp = {20,19,18,12,9,17,7,5,13,15,6,16,14};
    for(auto num: tmp)
    {
        k1.insert(num, num);
    }
    REQUIRE( getSuccessor(k1.testFindKey(12))->key == 13 );

    CrumpleTree<unsigned, std::string> k2;
    std::vector<unsigned> tmp2 = {20,19,18,12,9,17,7,5,13,15,6,16,14};
    for(auto num: tmp2)
    {
        k2.insert(num, "num");
    }
    REQUIRE( getSuccessor(k1.testFindKey(18))->key == 19 );

    CrumpleTree<std::string, std::string> k3;
    std::vector<std::string> tmp3 = {"t","s","r","l","i","q","g","e","m","o","f","p","n"};
    for(auto word: tmp3)
    {
        k3.insert(word, "num");
    }
    REQUIRE( getSuccessor(k3.testFindKey("l"))->key == "m" );

    CrumpleTree<std::string, unsigned> k4;
    std::vector<std::string> tmp4 = {"t","s","r","l","i","q","g","e","m","o","f","p","n"};
    for(auto word: tmp4)
    {
        k4.insert(word, 0);
    }
    REQUIRE( getSuccessor(k4.testFindKey("o"))->key == "p" );
}

TEST_CASE("swapsforRemoveRecursive", "[Helper],[Swap]")
{
    CrumpleTree<unsigned, unsigned> k1;
    std::vector<unsigned> tmp = {20,19,18,12,9,17,7,5,13,15,6,16,14};
    for(auto num: tmp)
    {
        k1.insert(num, num);
    }
    Node<unsigned, unsigned>* twelve = swapNodeToRemoveToLeaf(k1.testFindKey(12));
    REQUIRE( twelve->key == 12 );
    REQUIRE( twelve->level == 1 );
    REQUIRE( twelve->parent->key == 7 );

    CrumpleTree<unsigned, std::string> k2;
    std::vector<unsigned> tmp2 = {20,19,18,12,9,17,7,5,13,15,6,16,14};
    for(auto num: tmp2)
    {
        k2.insert(num, "num");
    }
    Node<unsigned, std::string>* eighteen = swapNodeToRemoveToLeaf(k2.testFindKey(18));
    REQUIRE( eighteen->key == 18 );
    REQUIRE( eighteen->level == 1 );
    REQUIRE( eighteen->parent->key == 16 );

    CrumpleTree<std::string, std::string> k3;
    std::vector<std::string> tmp3 = {"t","s","r","l","i","q","g","e","m","o","f","p","n"};
    for(auto word: tmp3)
    {
        k3.insert(word, "num");
    }
    Node<std::string, std::string>* e = swapNodeToRemoveToLeaf(k3.testFindKey("e"));
    REQUIRE( e->key == "e" );
    REQUIRE( e->parent->key == "f" );
    REQUIRE( e->level == 1 );

    CrumpleTree<std::string, unsigned> k4;
    std::vector<std::string> tmp4 = {"t","s","r","l","i","q","g","e","m","o","f","p","n"};
    for(auto word: tmp4)
    {
        k4.insert(word, 0);
    }
    Node<std::string, unsigned>* q = swapNodeToRemoveToLeaf(k4.testFindKey("q"));
    REQUIRE( q->key == "q" );
    REQUIRE( q->parent->key == "p" );
    REQUIRE( q->level == 1 );
}

TEST_CASE("deleteLeaf", "[Helper]")
{
    CrumpleTree<unsigned, unsigned> k1;
    k1.insert(1,1);
    Node<unsigned, unsigned>* root = k1.testGetRoot();
    k1.deleteLeaf(k1.testFindKey(1));
    REQUIRE( k1.testFindKey(1) == nullptr );
    REQUIRE( k1.testGetRoot() == nullptr );

    k1.insert(1,1);
    k1.insert(2,2);
    k1.insert(0,0);
    k1.deleteLeaf(k1.testFindKey(2));
    root = k1.testGetRoot();
    REQUIRE( root->right == nullptr );
    REQUIRE( root->left->key == 0 );

    k1.deleteLeaf(k1.testFindKey(0));
    REQUIRE( root->left == nullptr );
}

TEST_CASE("smallDeletes", "[Actual]")
{
    CrumpleTree<unsigned, unsigned> k1;
    std::vector<unsigned> tmp = {20,19,18,12,9,17,7,5,13,15,6,16,14};
    for(auto num: tmp)
    {
        k1.insert(num, num);
    }
    k1.remove(12);
    REQUIRE( k1.testGetRoot()->key == 9 );
    REQUIRE( k1.contains(12) == false );

    CrumpleTree<unsigned, std::string> k2;
    std::vector<unsigned> tmp2 = {20,19,18,12,9,17,7,5,13,15,6,16,14};
    for(auto num: tmp2)
    {
        k2.insert(num, "num");
    }
    k2.remove(18);
    REQUIRE( k2.testGetRoot()->key == 12 );
    REQUIRE( k2.contains(18) == false );

    CrumpleTree<std::string, std::string> k3;
    std::vector<std::string> tmp3 = {"t","s","r","l","i","q","g","e","m","o","f","p","n"};
    for(auto word: tmp3)
    {
        k3.insert(word, "num");
    }
    k3.remove("l");
    REQUIRE( k3.testGetRoot()->key == "i" );
    REQUIRE( k3.contains("l") == false );

    CrumpleTree<std::string, unsigned> k4;
    std::vector<std::string> tmp4 = {"t","s","r","l","i","q","g","e","m","o","f","p","n"};
    for(auto word: tmp4)
    {
        k4.insert(word, 0);
    }
    k4.remove("r");
    REQUIRE( k4.testGetRoot()->key == "l" );
    REQUIRE( k4.contains("r") == false );
}

TEST_CASE("removeChild", "[Helper]")
{
    CrumpleTree<unsigned, unsigned> k1;
    std::vector<unsigned> tmp = {20,19,18};
    for(auto num: tmp)
    {
        k1.insert(num, num);
    }
    Node<unsigned, unsigned>* l1 = k1.testGetRoot()->left;
    Node<unsigned, unsigned>* r1 = k1.testGetRoot()->right;
    k1.removeChildFromParent(k1.testFindKey(18));
    REQUIRE( k1.testGetRoot()->left == nullptr );
    k1.removeChildFromParent(k1.testFindKey(20));
    REQUIRE( k1.testGetRoot()->right == nullptr );
    delete l1;
    delete r1;

    CrumpleTree<unsigned, std::string> k2;
    std::vector<unsigned> tmp2 = {20,19,18};
    for(auto num: tmp2)
    {
        k2.insert(num, "num");
    }
    Node<unsigned, std::string>* l2 = k2.testGetRoot()->left;
    Node<unsigned, std::string>* r2 = k2.testGetRoot()->right;
    k2.removeChildFromParent(k2.testFindKey(18));
    REQUIRE( k2.testGetRoot()->left == nullptr );
    k2.removeChildFromParent(k2.testFindKey(20));
    REQUIRE( k2.testGetRoot()->right == nullptr );
    delete l2;
    delete r2;

    CrumpleTree<std::string, std::string> k3;
    std::vector<std::string> tmp3 = {"t","s","r"};
    for(auto word: tmp3)
    {
        k3.insert(word, "num");
    }
    Node<std::string, std::string>* l3 = k3.testGetRoot()->left;
    Node<std::string, std::string>* r3 = k3.testGetRoot()->right;
    k3.removeChildFromParent(k3.testFindKey("r"));
    REQUIRE( k3.testGetRoot()->left == nullptr );
    k3.removeChildFromParent(k3.testFindKey("t"));
    REQUIRE( k3.testGetRoot()->right == nullptr );
    delete l3;
    delete r3;

    CrumpleTree<std::string, unsigned> k4;
    std::vector<std::string> tmp4 = {"t","s","r"};
    for(auto word: tmp4)
    {
        k4.insert(word, 0);
    }
    Node<std::string, unsigned>* l4 = k4.testGetRoot()->left;
    Node<std::string, unsigned>* r4 = k4.testGetRoot()->right;
    k4.removeChildFromParent(k4.testFindKey("r"));
    REQUIRE( k4.testGetRoot()->left == nullptr );
    k4.removeChildFromParent(k4.testFindKey("t"));
    REQUIRE( k4.testGetRoot()->right == nullptr );
    delete l4;
    delete r4;
}

TEST_CASE("recursiveSwapRemoves", "[Actual]")
{
    CrumpleTree<unsigned, unsigned> k1;
    std::vector<unsigned> tmp = {20,19,18,12,9,17,7,5,13,15,6,16,14,1,21};
    for(auto num: tmp)
    {
        k1.insert(num, num);
    }
    k1.remove(7);
    REQUIRE( k1.contains(7) == false );
    REQUIRE( k1.getLevel(6) == 3 );

    CrumpleTree<unsigned, std::string> k2;
    std::vector<unsigned> tmp2 = {20,19,18,12,9,17,7,5,13,15,6,16,14,1,21};
    for(auto num: tmp2)
    {
        k2.insert(num, "num");
    }
    k2.remove(20);
    REQUIRE( k2.contains(20) == false );
    REQUIRE( k2.getLevel(19) == 2 );

    CrumpleTree<std::string, std::string> k3;
    std::vector<std::string> tmp3 = {"t","s","r","l","i","q","g","e","m","o","f","p","n","a","u"};
    for(auto word: tmp3)
    {
        k3.insert(word, "num");
    }
    k3.remove("g");
    REQUIRE( k3.contains("g") == false );
    REQUIRE( k3.getLevel("f") == 3 );

    CrumpleTree<std::string, unsigned> k4;
    std::vector<std::string> tmp4 = {"t","s","r","l","i","q","g","e","m","o","f","p","n","a","u"};
    for(auto word: tmp4)
    {
        k4.insert(word, 0);
    }
    k4.remove("t");
    REQUIRE( k4.contains("t") == false );
    REQUIRE( k4.getLevel("s") == 2 );
}

TEST_CASE("removeSingleAndEmpty", "[Actual]")
{
    CrumpleTree<unsigned, unsigned> k1;
    k1.remove(10);
    REQUIRE( k1.size() == 0 );
    REQUIRE( k1.isEmpty() == true );
    REQUIRE( k1.testGetRoot() == nullptr );
    k1.insert(10,5);
    REQUIRE( k1.isEmpty() == false );
    REQUIRE( k1.contains(10) == true );
    REQUIRE( k1.find(10) == 5 );
    k1.remove(10);
    REQUIRE( k1.isEmpty() == true );
    REQUIRE_THROWS_AS( k1.find(10), ElementNotFoundException ); 
    REQUIRE( k1.testGetRoot() == nullptr );
}

TEST_CASE("removeOtherTypes", "[Actual]")
{
    CrumpleTree<unsigned, unsigned> k1;
    k1.insert(10,10);
    REQUIRE( k1.contains(10) == true );
    REQUIRE( k1.find(10) == 10 );
    k1.remove(10);
    REQUIRE( k1.contains(10) == false );

    CrumpleTree<std::string, unsigned> k2;
    k2.insert("nathan", 10);
    REQUIRE( k2.contains("nathan") == true );
    REQUIRE( k2.find("nathan") == 10 );
    k2.remove("nathan");
    REQUIRE( k2.contains("nathan") == false );

    CrumpleTree<unsigned, std::string> k3;
    k3.insert(10,"nathan");
    REQUIRE( k3.contains(10) == true );
    REQUIRE( k3.find(10) == "nathan" );
    k3.remove(10);
    REQUIRE( k3.contains(10) == false );

    CrumpleTree<std::string, std::string> k4;
    k4.insert("nathan", "blah");
    REQUIRE( k4.contains("nathan") == true );
    REQUIRE( k4.find("nathan") == "blah" );
    k4.remove("nathan"); 
    REQUIRE( k4.contains("nathan") == false );
}

TEST_CASE("contains", "[Actual]")
{
    CrumpleTree<unsigned, unsigned> k1;
    REQUIRE( k1.contains(10) == false );
    k1.insert(10,10);
    REQUIRE( k1.contains(10) == true );

    CrumpleTree<unsigned, std::string> k2;
    REQUIRE( k2.contains(10) == false );
    k2.insert(10,"10");
    REQUIRE( k2.contains(10) == true );

    CrumpleTree<std::string, unsigned> k3;
    REQUIRE( k3.contains("10") == false );
    k3.insert("10",10);
    REQUIRE( k3.contains("10") == true );

    CrumpleTree<std::string, std::string> k4;
    REQUIRE( k4.contains("10") == false );
    k4.insert("10","10");
    REQUIRE( k4.contains("10") == true );
}

TEST_CASE("getShape", "[Helper]")
{
    Node<unsigned, unsigned>* root = new Node<unsigned, unsigned>(10,10,3);
    REQUIRE( getShape(root).left == 3 );
    REQUIRE( getShape(root).right == 3 );

    Node<unsigned, unsigned>* five = new Node<unsigned, unsigned>(5,5,2,root);
    root->left = five;
    REQUIRE( getShape(five).left == 2 );
    REQUIRE( getShape(five).right == 2 );

    REQUIRE( getShape(root).left == 1 );
    REQUIRE( getShape(root).right == 3 );

    Node<unsigned, unsigned>* eleven = new Node<unsigned, unsigned>(11,11,1,root);
    root->right = eleven;
    REQUIRE( getShape(eleven).left == 1 );
    REQUIRE( getShape(eleven).right == 1 );

    REQUIRE( getShape(root).left == 1 );
    REQUIRE( getShape(root).right == 2 );

    Node<unsigned, unsigned>* six = new Node<unsigned, unsigned>(6,6,1,five);
    five->right = six;
    REQUIRE( getShape(six).left == 1 );
    REQUIRE( getShape(six).right == 1 );

    REQUIRE( getShape(five).left == 2 );
    REQUIRE( getShape(five).right == 1 );

    Node<unsigned, unsigned>* four = new Node<unsigned, unsigned>(4,4,2,five);
    five->left = four;
    REQUIRE( getShape(four).left == 2 );
    REQUIRE( getShape(four).right == 2 );

    REQUIRE( getShape(five).left == 0 );
    REQUIRE( getShape(five).right == 1 );

    delete root;
    delete five;
    delete eleven;
    delete six;
    delete four;
}

TEST_CASE("validShapes", "[Helper]")
{
    std::vector<Node<unsigned, unsigned>*> nodes = {};
    Node<unsigned, unsigned>* ten = new Node<unsigned, unsigned>(10, 10, 4);
    Node<unsigned, unsigned>* five = new Node<unsigned, unsigned>(5, 5, 2, ten);
    Node<unsigned, unsigned>* fifteen = new Node<unsigned, unsigned>(15, 15, 2, ten);
    ten->left = five;
    ten->right = fifteen;
    Node<unsigned, unsigned>* three = new Node<unsigned, unsigned>(3, 3, 1, five);
    five->left = three;
    Node<unsigned, unsigned>* twenty = new Node<unsigned, unsigned>(20, 20, 1, fifteen);
    fifteen->right = twenty;
    nodes.push_back(ten);
    nodes.push_back(five);
    nodes.push_back(fifteen);
    nodes.push_back(three);
    nodes.push_back(twenty);

    for(auto node : nodes){
        REQUIRE( isValidNodeShape(node) == true );
        delete node;
    }
}

TEST_CASE("invalidShapes", "[Helper]")
{
    std::vector<Node<unsigned, unsigned>*> nodes = {};
    Node<unsigned, unsigned>* ten = new Node<unsigned, unsigned>(10, 10, 4);
    Node<unsigned, unsigned>* five = new Node<unsigned, unsigned>(5, 5, 3, ten);
    Node<unsigned, unsigned>* fifteen = new Node<unsigned, unsigned>(15, 15, 1, ten);
    ten->left = five;
    ten->right = fifteen;
    Node<unsigned, unsigned>* twenty = new Node<unsigned, unsigned>(20, 20, 1, fifteen);
    fifteen->right = twenty;
    Node<unsigned, unsigned>* three = new Node<unsigned, unsigned>(3, 3, 3, five);
    five->left = three;


    nodes.push_back(ten);
    nodes.push_back(five);
    nodes.push_back(fifteen);
    nodes.push_back(three);

    Node<unsigned, unsigned>* two = new Node<unsigned, unsigned>(2,2,3);
    Node<unsigned, unsigned>* one = new Node<unsigned, unsigned>(1,1,1, two);
    two->left = one;
    Node<unsigned, unsigned>* zero = new Node<unsigned, unsigned>(0,0,1,one);
    one->left = zero;

    nodes.push_back(two);
    nodes.push_back(one);

    for(auto node : nodes){
        REQUIRE( isValidNodeShape(node) == false );
        delete node;
    }
    delete twenty;
    delete zero;
}

TEST_CASE("sideOfParent", "[Helper]")
{
    CrumpleTree<unsigned, unsigned> k1;
    k1.insert(10,10);
    k1.insert(5,5);
    k1.insert(15,15);
    REQUIRE( sideOfParent(k1.testFindKey(5)) == 'l' );
    REQUIRE( sideOfParent(k1.testFindKey(15)) == 'r' );
}

TEST_CASE("insertRootCausesNoRebalance", "[Actual]")
{
    CrumpleTree<unsigned, unsigned> k1;
    k1.insert(5,5);
    REQUIRE( k1.testGetRoot()->key == 5 );
    REQUIRE( getShape(k1.testGetRoot()).left == 1 );
    REQUIRE( getShape(k1.testGetRoot()).right == 1 );
    REQUIRE( k1.getLevel(5) == 1 );
    
    CrumpleTree<unsigned, std::string> k2;
    k2.insert(5,"nathan");
    REQUIRE( k2.testGetRoot()->key == 5 );
    REQUIRE( getShape(k2.testGetRoot()).left == 1 );
    REQUIRE( getShape(k2.testGetRoot()).right == 1 );
    REQUIRE( k2.getLevel(5) == 1 );

    CrumpleTree<std::string, std::string> k3;
    k3.insert("nathan","nathan");
    REQUIRE( k3.testGetRoot()->key == "nathan" );
    REQUIRE( getShape(k3.testGetRoot()).left == 1 );
    REQUIRE( getShape(k3.testGetRoot()).right == 1 );
    REQUIRE( k3.getLevel("nathan") == 1 );
    
    CrumpleTree<std::string, unsigned> k4;
    k4.insert("nathan",5);
    REQUIRE( k4.testGetRoot()->key == "nathan" );
    REQUIRE( getShape(k4.testGetRoot()).left == 1 );
    REQUIRE( getShape(k4.testGetRoot()).right == 1 );
    REQUIRE( k4.getLevel("nathan") == 1 );
}

TEST_CASE("insertCase2", "[Actual]")
{
    CrumpleTree<unsigned, unsigned> k1;
    k1.insert(10,10);
    k1.insert(5,5);
    REQUIRE( k1.size() == 2 );
    REQUIRE( k1.testFindKey(5)->key == 5 );
    REQUIRE( k1.testFindKey(5)->parent == k1.testGetRoot() );
    REQUIRE( k1.testFindKey(5)->left == nullptr );
    REQUIRE( k1.testFindKey(5)->right == nullptr );
    REQUIRE( (getShape(k1.testFindKey(5)).left == 1 && getShape(k1.testFindKey(5)).right == 1) );
    REQUIRE( k1.testGetRoot()->key == 10 );
    REQUIRE( k1.testGetRoot()->left->key == 5 );
    REQUIRE( k1.testGetRoot()->right == nullptr );
    REQUIRE( k1.getLevel(5) == 1 );
    REQUIRE( k1.getLevel(10) == 2 );
    REQUIRE( (getShape(k1.testGetRoot()).left == 1 && getShape(k1.testGetRoot()).right == 2) );
    k1.insert(15,15);
    REQUIRE( (getShape(k1.testGetRoot()).left == 1 && getShape(k1.testGetRoot()).right == 1) );
    REQUIRE( k1.getLevel(10) == 2 );
    REQUIRE( k1.getLevel(15) == 1 );

    CrumpleTree<unsigned, unsigned> k2;
    k2.insert(10,10);
    k2.insert(15,15);
    REQUIRE( (getShape(k2.testGetRoot()).left == 2 && getShape(k2.testGetRoot()).right == 1) );
    REQUIRE( k2.getLevel(10) == 2 );

    CrumpleTree<unsigned, std::string> k3;
    k3.insert(10,"nathan");
    k3.insert(15,"nathan");
    REQUIRE( (getShape(k3.testGetRoot()).left == 2 && getShape(k3.testGetRoot()).right == 1) );
    REQUIRE( k3.getLevel(10) == 2 );

    CrumpleTree<std::string, unsigned> k4;
    k4.insert("b", 5);
    k4.insert("a",1);
    REQUIRE( (getShape(k4.testGetRoot()).left == 1 && getShape(k4.testGetRoot()).right == 2) );

    CrumpleTree<std::string, std::string> k5;
    k5.insert("a", "z");
    k5.insert("b","");
    REQUIRE( (getShape(k5.testGetRoot()).left == 2 && getShape(k5.testGetRoot()).right == 1) );
}

TEST_CASE("insertCase3", "[Actual]")
{
    Node<unsigned, unsigned>* ten = new Node<unsigned, unsigned>(10,10,3);
    Node<unsigned, unsigned>* eleven = new Node<unsigned, unsigned>(11,11,1,ten);
    ten->right = eleven;
    Node<unsigned, unsigned>* five = new Node<unsigned, unsigned>(5,5,3,ten);
    ten->left = five;
    Node<unsigned, unsigned>* three = new Node<unsigned, unsigned>(3,3,2,five);
    five->left = three;
    Node<unsigned, unsigned>* seven = new Node<unsigned, unsigned>(7,7,1,five);
    five->right = seven;
    Node<unsigned, unsigned>* two = new Node<unsigned, unsigned>(2,2,1,three);
    three->left = two;
    Node<unsigned, unsigned>* four = new Node<unsigned, unsigned>(4,4,1,three);
    three->right = four;
    Node<unsigned, unsigned>* root = insertRebalanceCase3(five, 'l');
    REQUIRE( root-> key == 5 );
    REQUIRE( (getShape(root).left == 1 && getShape(root).right == 1) );
    REQUIRE( root->parent == nullptr );
    REQUIRE( root->left->key == 3 );
    REQUIRE( root->left->parent == root );
    REQUIRE( root->left->left->key == 2 );
    REQUIRE( root->left->left->parent->key == 3 );
    REQUIRE( (getShape(root->left).left == 1 && getShape(root->left).right == 1) );
    REQUIRE( root->right->key == 10 );
    REQUIRE( root->right->parent == root );
    REQUIRE( root->right->left->key == 7 );
    REQUIRE( root->right->left->parent->key == 10 );
    REQUIRE( root->right->right->key == 11 );
    REQUIRE( (getShape(root->right).left == 1 && getShape(root->right).right == 1) );
    REQUIRE( root->left->right->key == 4 );
    REQUIRE( root->left->right->parent->key == 3 );
    REQUIRE( root->level == 3 );
    REQUIRE( root->left->level == 2 );
    REQUIRE( root->right->level == 2 );

    postOrderDelete(root);

    Node<unsigned, unsigned>* parent = new Node<unsigned, unsigned>(1000, 1000, 4);
    Node<unsigned, unsigned>* hundred = new Node<unsigned, unsigned>(100,100,3,parent);
    parent->left = hundred;
    Node<unsigned, unsigned>* hundredOne = new Node<unsigned, unsigned>(101,101,1,hundred);
    hundred->right = hundredOne;
    Node<unsigned, unsigned>* ninety = new Node<unsigned, unsigned>(90,90,3,hundred);
    hundred->left = ninety;
    Node<unsigned, unsigned>* eighty = new Node<unsigned, unsigned>(80,80,2,ninety);
    ninety->left = eighty;
    Node<unsigned, unsigned>* ninetyfive = new Node<unsigned, unsigned>(95,95,1,ninety);
    ninety->right = ninetyfive;
    Node<unsigned, unsigned>* newRoot = insertRebalanceCase3(ninety, 'l');
    REQUIRE( newRoot->key == 90 );

    REQUIRE( hundred->level == 2 );
    REQUIRE( hundred->parent->key == 90 );
    REQUIRE( hundred->left->key == 95 );
    REQUIRE( hundred->right->key == 101 );

    REQUIRE( ninetyfive->level == 1 );
    REQUIRE( ninetyfive->parent->key == 100 );
    REQUIRE( ninetyfive->left == nullptr );
    REQUIRE( ninetyfive->right == nullptr );

    REQUIRE( hundredOne->level == 1 );
    REQUIRE( hundredOne->parent->key == 100 );
    REQUIRE( hundredOne->left == nullptr );
    REQUIRE( hundredOne->right == nullptr );

    REQUIRE( ninety->level == 3 );
    REQUIRE( ninety->parent->key == 1000 );
    REQUIRE( ninety->left->key == 80 );
    REQUIRE( ninety->right->key == 100 );

    REQUIRE( eighty->level == 2 );
    REQUIRE( eighty->parent->key == 90 );
    REQUIRE( eighty->left == nullptr );
    REQUIRE( eighty->right == nullptr );

    REQUIRE( parent->left->key == 90 );

    postOrderDelete(ninety);
    delete parent;
}

TEST_CASE("insertCase3Mirror", "[Actual]")
{
    Node<unsigned, unsigned>* fifteen = new Node<unsigned, unsigned>(15,15,3);
    Node<unsigned, unsigned>* ten = new Node<unsigned, unsigned>(10,10,1,fifteen);
    fifteen->left = ten;
    Node<unsigned, unsigned>* twenty = new Node<unsigned, unsigned>(20,20,3,fifteen);
    fifteen->right = twenty;
    Node<unsigned, unsigned>* seventeen = new Node<unsigned, unsigned>(17,16,1,twenty);
    twenty->left = seventeen;
    Node<unsigned, unsigned>* twentytwo = new Node<unsigned, unsigned>(22,22,2,twenty);
    twenty->right = twentytwo;

    Node<unsigned, unsigned>* root = insertRebalanceCase3(twenty, 'r');
    REQUIRE( root->key == 20 );
    REQUIRE( root->parent == nullptr );
    REQUIRE( root->left->key == 15 );
    REQUIRE( root->right->key == 22 );
    REQUIRE( (getShape(root).left == 1 && getShape(root).right == 1) );

    REQUIRE( fifteen->parent->key == 20 );
    REQUIRE( fifteen->left->key == 10 );
    REQUIRE( fifteen->right->key == 17 );
    REQUIRE( (getShape(fifteen).left == 1 && getShape(fifteen).right == 1) );

    REQUIRE( ten->parent->key == 15 );
    REQUIRE( ten->left == nullptr );
    REQUIRE( ten->right == nullptr );
    REQUIRE( (getShape(ten).left == 1 && getShape(ten).right == 1) );

    REQUIRE( seventeen->parent->key == 15 );
    REQUIRE( seventeen->left == nullptr );
    REQUIRE( seventeen->right == nullptr );
    REQUIRE( (getShape(seventeen).left == 1 && getShape(seventeen).right == 1) );

    REQUIRE( twentytwo->parent->key == 20 );
    REQUIRE( twentytwo->left == nullptr );
    REQUIRE( twentytwo->right == nullptr );
    REQUIRE( (getShape(twentytwo).left == 2 && getShape(twentytwo).right == 2) );

    postOrderDelete(root);
}

TEST_CASE("insertCase4", "[Actual]")
{
    Node<unsigned, unsigned>* ten = new Node<unsigned, unsigned>(10,10,4);
    Node<unsigned, unsigned>* five = new Node<unsigned, unsigned>(5,5,4,ten);
    ten->left = five;
    Node<unsigned, unsigned>* twelve = new Node<unsigned, unsigned>(12,12,2,ten);
    ten->right = twelve;
    Node<unsigned, unsigned>* eight = new Node<unsigned, unsigned>(8,8,3,five);
    five->right = eight;
    Node<unsigned, unsigned>* three = new Node<unsigned, unsigned>(3,3,3,five);
    five->left = three;
    
    Node<unsigned, unsigned>* root = insertRebalanceCase4(five, 'l');
    REQUIRE( root->key == 5 );

    REQUIRE( five->parent == nullptr );
    REQUIRE( five->level == 5 );
    REQUIRE( five->right->key == 10 );
    REQUIRE( five->left->key == 3 );
    REQUIRE( (getShape(five).left == 2 && getShape(five).right == 1) );

    REQUIRE( ten->parent->key == 5 );
    REQUIRE( ten->level == 4 );
    REQUIRE( ten->right->key == 12 );
    REQUIRE( ten->left->key == 8 );
    REQUIRE( (getShape(ten).left == 1 && getShape(ten).right == 2) );

    REQUIRE( eight->parent->key == 10 );
    REQUIRE( eight->level == 3 );
    REQUIRE( eight->right == nullptr );
    REQUIRE( eight->left == nullptr );
    REQUIRE( (getShape(eight).left == 3 && getShape(eight).right == 3) );

    REQUIRE( twelve->parent->key == 10 );
    REQUIRE( twelve->level == 2 );
    REQUIRE( twelve->right == nullptr );
    REQUIRE( twelve->left == nullptr );
    REQUIRE( (getShape(twelve).left == 2 && getShape(twelve).right == 2) );

    REQUIRE( three->parent->key == 5 );
    REQUIRE( three->level == 3 );
    REQUIRE( three->right == nullptr );
    REQUIRE( three->left == nullptr );
    REQUIRE( (getShape(three).left == 3 && getShape(three).right == 3) );

    postOrderDelete(root);
}

TEST_CASE("insertCase4Mirror", "[Actual]")
{
    Node<unsigned, unsigned>* parent = new Node<unsigned, unsigned>(17,17,5);
    Node<unsigned, unsigned>* ten = new Node<unsigned, unsigned>(10,10,4,parent);
    parent->right = ten;
    Node<unsigned, unsigned>* fifteen = new Node<unsigned, unsigned>(15,15,4,ten);
    ten->right = fifteen;
    Node<unsigned, unsigned>* five = new Node<unsigned, unsigned>(5,5,2,ten);
    ten->left = five;
    Node<unsigned, unsigned>* twelve = new Node<unsigned, unsigned>(12,12,3,fifteen);
    fifteen->left = twelve;
    Node<unsigned, unsigned>* twenty = new Node<unsigned, unsigned>(20,20,3,fifteen);
    fifteen->right = twenty;

    Node<unsigned, unsigned>* newRoot = insertRebalanceCase4(fifteen, 'r');
    REQUIRE( newRoot->key == 15 );
    REQUIRE( parent->right->key == 15 );

    REQUIRE( fifteen->parent->key == 17 );
    REQUIRE( fifteen->left->key == 10 );
    REQUIRE( fifteen->right->key == 20 );
    REQUIRE( fifteen->level == 5 );
    REQUIRE( (getShape(fifteen).left == 1 && getShape(fifteen).right == 2) );
    
    REQUIRE( ten->parent->key == 15 );
    REQUIRE( ten->left->key == 5 );
    REQUIRE( ten->right->key == 12 );
    REQUIRE( ten->level == 4 );
    REQUIRE( (getShape(ten).left == 2 && getShape(ten).right == 1) );

    REQUIRE( twenty->parent->key == 15 );
    REQUIRE( twenty->left == nullptr );
    REQUIRE( twenty->right == nullptr );
    REQUIRE( twenty->level == 3 );
    REQUIRE( (getShape(twenty).left == 3 && getShape(twenty).right == 3) );

    REQUIRE( twelve->parent->key == 10 );
    REQUIRE( twelve->left == nullptr );
    REQUIRE( twelve->right == nullptr );
    REQUIRE( twelve->level == 3 );
    REQUIRE( (getShape(twelve).left == 3 && getShape(twelve).right == 3) );

    REQUIRE( five->parent->key == 10 );
    REQUIRE( five->left == nullptr );
    REQUIRE( five->right == nullptr );
    REQUIRE( five->level == 2 );
    REQUIRE( (getShape(five).left == 2 && getShape(five).right == 2 ) );

    postOrderDelete(parent);
}

TEST_CASE("insertCase5", "[Actual]")
{
    Node<unsigned, unsigned>* twenty = new Node<unsigned, unsigned>(20,20,3);
    Node<unsigned, unsigned>* ten = new Node<unsigned, unsigned>(10,10,3,twenty);
    twenty->left = ten;
    Node<unsigned, unsigned>* thirty = new Node<unsigned, unsigned>(30,30,1,twenty);
    twenty->right = thirty;
    Node<unsigned, unsigned>* two = new Node<unsigned, unsigned>(2,2,1,ten);
    ten->left = two;
    Node<unsigned, unsigned>* five = new Node<unsigned, unsigned>(5,5,2,ten);
    ten->right = five;
    Node<unsigned, unsigned>* three = new Node<unsigned, unsigned>(3,3,1,five);
    five->left = three;
    Node<unsigned, unsigned>* six = new Node<unsigned, unsigned>(6,6,1,five);
    five->right = six;
    
    Node<unsigned, unsigned>* root = insertRebalanceCase5(ten, 'l');

    REQUIRE( root->key == 5 );

    REQUIRE( five->parent == nullptr );
    REQUIRE( five->level == 3 );
    REQUIRE( five->left->key == 10 );
    REQUIRE( five->right->key == 20 );
    REQUIRE( (getShape(five).left == 1 && getShape(five).right == 1) );

    REQUIRE( ten->parent->key == 5 );
    REQUIRE( ten->level == 2 );
    REQUIRE( ten->left->key == 2 );
    REQUIRE( ten->right->key == 3 );
    REQUIRE( (getShape(ten).left == 1 && getShape(ten).right == 1) );

    REQUIRE( two->parent->key == 10 );
    REQUIRE( two->level == 1 );
    REQUIRE( two->left == nullptr );
    REQUIRE( two->right == nullptr );
    REQUIRE( (getShape(two).left == 1 && getShape(two).right == 1) );

    REQUIRE( three->parent->key == 10 );
    REQUIRE( three->level == 1 );
    REQUIRE( three->left == nullptr );
    REQUIRE( three->right == nullptr );
    REQUIRE( (getShape(three).left == 1 && getShape(three).right == 1) );

    REQUIRE( twenty->parent->key == 5 );
    REQUIRE( twenty->level == 2 );
    REQUIRE( twenty->left->key == 6 );
    REQUIRE( twenty->right->key == 30 );
    REQUIRE( (getShape(twenty).left == 1 && getShape(twenty).right == 1) );

    REQUIRE( six->parent->key == 20 );
    REQUIRE( six->level == 1 );
    REQUIRE( six->left == nullptr );
    REQUIRE( six->right == nullptr );
    REQUIRE( (getShape(six).left == 1 && getShape(six).right == 1) );

    REQUIRE( thirty->parent->key == 20 );
    REQUIRE( thirty->level == 1 );
    REQUIRE( thirty->left == nullptr );
    REQUIRE( thirty->right == nullptr );
    REQUIRE( (getShape(thirty).left == 1 && getShape(thirty).right == 1) );

    postOrderDelete(root);
}

TEST_CASE("insertCase5Mirror", "[Actual]")
{
    Node<unsigned, unsigned>* parent = new Node<unsigned, unsigned>(5,5,4);
    Node<unsigned, unsigned>* one = new Node<unsigned, unsigned>(1,1,3,parent);
    parent->left = one;
    Node<unsigned, unsigned>* three = new Node<unsigned, unsigned>(3,3,3,one);
    one->right = three;
    Node<unsigned, unsigned>* zero = new Node<unsigned, unsigned>(0,0,1,one);
    one->left = zero;
    Node<unsigned, unsigned>* two = new Node<unsigned, unsigned>(2,2,2,three);
    three->left = two;
    Node<unsigned, unsigned>* four = new Node<unsigned, unsigned>(4,4,1,three);
    three->right = four;

    Node<unsigned, unsigned>* root = insertRebalanceCase5(three, 'r');
    REQUIRE( root->key == 2 );
    REQUIRE( parent->left->key == 2 );
    REQUIRE( parent->level == 4 );

    REQUIRE( two->parent->key == 5 );
    REQUIRE( two->level == 3 );
    REQUIRE( two->left->key == 1 );
    REQUIRE( two->right->key == 3 );
    REQUIRE( (getShape(two).left == 1 && getShape(two).right == 1) );

    REQUIRE( one->parent->key == 2 );
    REQUIRE( one->level == 2 );
    REQUIRE( one->left->key == 0 );
    REQUIRE( one->right == nullptr );
    REQUIRE( (getShape(one).left == 1 && getShape(one).right == 2) );

    REQUIRE( three->parent->key == 2 );
    REQUIRE( three->level == 2 );
    REQUIRE( three->left == nullptr );
    REQUIRE( three->right->key == 4 );
    REQUIRE( (getShape(three).left == 2 && getShape(three).right == 1) );

    REQUIRE( zero->parent->key == 1 );
    REQUIRE( zero->level == 1 );
    REQUIRE( zero->left == nullptr );
    REQUIRE( zero->right == nullptr );
    REQUIRE( (getShape(zero).left == 1 && getShape(zero).right == 1) );

    REQUIRE( four->parent->key == 3 );
    REQUIRE( four->level == 1 );
    REQUIRE( four->left == nullptr );
    REQUIRE( four->right == nullptr );
    REQUIRE( (getShape(four).left == 1 && getShape(four).right == 1) );

    postOrderDelete(parent);
}

TEST_CASE("insertCrumple", "[Actual]")
{
    CrumpleTree<unsigned, unsigned> k1;
    k1.insert(20,20);
    k1.insert(19,19);
    k1.insert(18,18);
    REQUIRE( k1.getLevel(20) == 1 );
    REQUIRE( k1.getLevel(19) == 2 );
    REQUIRE( k1.getLevel(18) == 1 );
    REQUIRE( k1.testGetRoot()->key == 19 );
    k1.insert(12,12);
    k1.insert(9,9);
    k1.insert(17,17);
    REQUIRE( k1.getLevel(18) == 3 );
    REQUIRE( k1.getLevel(12) == 2 );
    REQUIRE( k1.getLevel(19) == 2 );
    REQUIRE( k1.getLevel(9) == 1 );
    REQUIRE( k1.getLevel(17) == 1 );
    REQUIRE( k1.getLevel(20) == 1 );
    k1.insert(7,7);
    k1.insert(5,5);
    k1.insert(13,13);
    k1.insert(15,15);
    k1.insert(6,6);
    k1.insert(16,16);
    k1.insert(14,14);
    REQUIRE( k1.getLevel(12) == 5 );
    REQUIRE( k1.getLevel(18) == 4 );
    REQUIRE( k1.getLevel(7) == 3 );
    REQUIRE( k1.getLevel(15) == 3 );
    REQUIRE( k1.getLevel(5) == 2 );
    REQUIRE( k1.getLevel(13) == 2 );
    REQUIRE( k1.getLevel(17) == 2 );
    REQUIRE( k1.getLevel(19) == 2 );
    REQUIRE( k1.getLevel(6) == 1 );
    REQUIRE( k1.getLevel(9) == 1 );
    REQUIRE( k1.getLevel(14) == 1 );
    REQUIRE( k1.getLevel(16) == 1 );
    REQUIRE( k1.getLevel(20) == 1 );
    std::vector<unsigned> k1exp = {6,5,9,7,14,13,16,17,15,20,19,18,12};
    REQUIRE( k1.postOrder() == k1exp );
}

TEST_CASE("insertCrumpleTemplated","[Actual]")
{
    CrumpleTree<int, int> k1;
    std::vector<int> tmp = {20,19,18,12,9,17,7,5,13,15,6,16,14};
    for(auto num: tmp)
    {
        k1.insert(num, num);
    }
    std::vector<int> expPostNum = {6,5,9,7,14,13,16,17,15,20,19,18,12};
    REQUIRE( k1.postOrder() == expPostNum );
    REQUIRE( k1.size() == 13 );
    REQUIRE( k1.isEmpty() == false );
    REQUIRE( k1.contains(6) );
    REQUIRE( k1.getLevel(6) == 1 );

    CrumpleTree<int, std::string> k2;
    std::vector<int> tmp2 = {20,19,18,12,9,17,7,5,13,15,6,16,14};
    for(auto num: tmp2)
    {
        k2.insert(num, "num");
    }
    REQUIRE( k2.postOrder() == expPostNum );
    REQUIRE( k2.size() == 13 );
    REQUIRE( k2.isEmpty() == false );
    REQUIRE( k2.contains(6) );
    REQUIRE( k2.getLevel(6) == 1 );

    CrumpleTree<std::string, std::string> k3;
    std::vector<std::string> tmp3 = {"t","s","r","l","i","q","g","e","m","o","f","p","n"};
    for(auto word: tmp3)
    {
        k3.insert(word, "num");
    }
    std::vector<std::string> expPostStr = {"f","e","i","g","n","m","p","q","o","t","s","r","l"};
    REQUIRE( k3.postOrder() == expPostStr );
    REQUIRE( k3.size() == 13 );
    REQUIRE( k3.isEmpty() == false );
    REQUIRE( k3.contains("f") );
    REQUIRE( k3.getLevel("f") == 1 );

    CrumpleTree<std::string, unsigned> k4;
    std::vector<std::string> tmp4 = {"t","s","r","l","i","q","g","e","m","o","f","p","n"};
    for(auto word: tmp4)
    {
        k4.insert(word, 0);
    }
    REQUIRE( k4.postOrder() == expPostStr );
    REQUIRE( k4.size() == 13 );
    REQUIRE( k4.isEmpty() == false );
    REQUIRE( k4.contains("f") );
    REQUIRE( k4.getLevel("f") == 1 );
}

TEST_CASE("removeRoot", "[Actual]")
{
    CrumpleTree<unsigned, unsigned> k1;
    k1.remove(5);
    REQUIRE( k1.size() == 0 );
    REQUIRE( k1.isEmpty() == true );
    k1.insert(5,5);
    k1.remove(5);
    REQUIRE( k1.size() == 0 );
    REQUIRE( k1.isEmpty() == true );
    REQUIRE( k1.testGetRoot() == nullptr );

    CrumpleTree<unsigned, std::string> k2;
    k2.remove(5);
    REQUIRE( k2.size() == 0 );
    REQUIRE( k2.isEmpty() == true );
    k2.insert(5,"");
    k2.remove(5);
    REQUIRE( k2.size() == 0 );
    REQUIRE( k2.isEmpty() == true );
    REQUIRE( k2.testGetRoot() == nullptr );

    CrumpleTree<std::string, unsigned> k3;
    k3.remove("");
    REQUIRE( k3.size() == 0 );
    REQUIRE( k3.isEmpty() == true );
    k3.insert("",0);
    k3.remove("");
    REQUIRE( k3.size() == 0 );
    REQUIRE( k3.isEmpty() == true );
    REQUIRE( k3.testGetRoot() == nullptr );

    CrumpleTree<std::string, std::string> k4;
    k4.remove("");
    REQUIRE( k4.size() == 0 );
    REQUIRE( k4.isEmpty() == true );
    k4.insert("","");
    k4.remove("");
    REQUIRE( k4.size() == 0 );
    REQUIRE( k4.isEmpty() == true );
    REQUIRE( k4.testGetRoot() == nullptr );
}

TEST_CASE("removeRebalanceCase1", "[Actual]")
{
    CrumpleTree<unsigned, unsigned> k1;
    k1.insert(5,5);
    k1.insert(3,3);
    k1.insert(6,6);

    k1.removeRebalance(k1.testFindKey(3), true);
    REQUIRE( k1.testGetRoot()->key == 5 );
    REQUIRE( k1.getLevel(5) == 2 );
    REQUIRE( k1.testGetRoot()->left == nullptr );
    REQUIRE( k1.testGetRoot()->right->key == 6 );
    REQUIRE( k1.getLevel(6) == 1 );
    REQUIRE( (getShape(k1.testFindKey(5)).left == 2 && getShape(k1.testFindKey(5)).right == 1) );

    CrumpleTree<unsigned, unsigned> k2;
    k2.insert(5,5);
    k2.insert(3,3);
    k2.insert(6,6);
    k2.removeRebalance(k2.testFindKey(6), true);
    REQUIRE( k2.testGetRoot()->key == 5 );
    REQUIRE( k2.getLevel(5) == 2 );
    REQUIRE( k2.testGetRoot()->right == nullptr );
    REQUIRE( k2.testGetRoot()->left->key == 3 );
    REQUIRE( k2.getLevel(3) == 1 );
    REQUIRE( (getShape(k2.testFindKey(5)).left == 1 && getShape(k2.testFindKey(5)).right == 2) );

    CrumpleTree<unsigned, std::string> k3;
    k3.insert(5,"");
    k3.insert(3,"");
    k3.insert(6,"");
    k3.removeRebalance(k3.testFindKey(3),true);
    REQUIRE( (getShape(k3.testFindKey(5)).left == 2 && getShape(k3.testFindKey(5)).right == 1) );

    CrumpleTree<std::string, std::string> k4;
    k4.insert("5","");
    k4.insert("3","");
    k4.insert("6","");
    k4.removeRebalance(k4.testFindKey("3"),true);
    REQUIRE( (getShape(k4.testFindKey("5")).left == 2 && getShape(k4.testFindKey("5")).right == 1) );

    CrumpleTree<std::string, unsigned> k5;
    k5.insert("5",1);
    k5.insert("3",1);
    k5.insert("6",1);
    k5.removeRebalance(k5.testFindKey("3"),true);
    REQUIRE( (getShape(k5.testFindKey("5")).left == 2 && getShape(k5.testFindKey("5")).right == 1) );
}

TEST_CASE("removeRebalanceCase1Part2","[Actual]")
{
    CrumpleTree<unsigned, unsigned> k1;
    k1.insert(5,5);
    k1.insert(3,3);
    k1.removeRebalance(k1.testFindKey(3), true);
    REQUIRE( k1.testGetRoot()->key == 5 ); 
    REQUIRE( k1.testGetRoot()->left == nullptr ); 
    REQUIRE( k1.testGetRoot()->right == nullptr ); 
    REQUIRE( k1.getLevel(5) == 1 ); 
    REQUIRE( (getShape(k1.testFindKey(5)).left == 1 && getShape(k1.testFindKey(5)).right == 1) );

    CrumpleTree<unsigned, unsigned> k2;
    k2.insert(5,5);
    k2.insert(6,6);
    k2.removeRebalance(k2.testFindKey(6), true);
    REQUIRE( k2.testGetRoot()->key == 5 ); 
    REQUIRE( k2.testGetRoot()->left == nullptr ); 
    REQUIRE( k2.testGetRoot()->right == nullptr ); 
    REQUIRE( k2.getLevel(5) == 1 ); 
    REQUIRE( (getShape(k2.testFindKey(5)).left == 1 && getShape(k2.testFindKey(5)).right == 1) );
}

TEST_CASE("removeRebalanceCase2", "[Actual]")
{
    CrumpleTree<unsigned, unsigned> k1;
    k1.insert(1,1);
    k1.insert(2,2);
    k1.insert(3,3);
    k1.insert(4,4);
    REQUIRE( k1.testGetRoot()->key == 2 );
    k1.remove(4);
    REQUIRE( k1.testGetRoot()->key == 2 );
    REQUIRE( k1.getLevel(2) == 3 );
    REQUIRE( (getShape(k1.testGetRoot()).left == 2 && getShape(k1.testGetRoot()).right == 2) );
    REQUIRE( k1.testGetRoot()->right->key == 3 );
    REQUIRE( k1.testGetRoot()->left->key == 1 );
    k1.remove(3);
    REQUIRE( (getShape(k1.testGetRoot()).left == 1 && getShape(k1.testGetRoot()).right == 2) );

    CrumpleTree<unsigned, std::string> k2;
    k2.insert(4,"4");
    k2.insert(3,"3");
    k2.insert(2,"2");
    k2.insert(1,"1");
    REQUIRE( k2.testGetRoot()->key == 3 );
    k2.remove(1);
    REQUIRE( k2.testGetRoot()->key == 3 );
    REQUIRE( k2.getLevel(3) == 3 );
    REQUIRE( (getShape(k2.testGetRoot()).left == 2 && getShape(k2.testGetRoot()).right == 2) );
    REQUIRE( k2.testGetRoot()->right->key == 4 );
    REQUIRE( k2.testGetRoot()->left->key == 2 );
    k2.remove(2);
    REQUIRE( (getShape(k2.testGetRoot()).left == 2 && getShape(k2.testGetRoot()).right == 1) );

    CrumpleTree<std::string, unsigned> k3;
    k3.insert("1",1);
    k3.insert("2",2);
    k3.insert("3",3);
    k3.insert("4",4);
    REQUIRE( k3.testGetRoot()->key == "2" );
    k3.remove("4");
    REQUIRE( k3.testGetRoot()->key == "2" );
    REQUIRE( k3.getLevel("2") == 3 );
    REQUIRE( (getShape(k3.testGetRoot()).left == 2 && getShape(k3.testGetRoot()).right == 2) );
    REQUIRE( k3.testGetRoot()->right->key == "3" );
    REQUIRE( k3.testGetRoot()->left->key == "1" );
    k3.remove("3");
    REQUIRE( (getShape(k3.testGetRoot()).left == 1 && getShape(k3.testGetRoot()).right == 2) );

    CrumpleTree<std::string, std::string> k4;
    k4.insert("4","4");
    k4.insert("3","3");
    k4.insert("2","2");
    k4.insert("1","1");
    REQUIRE( k4.testGetRoot()->key == "3" );
    k4.remove("1");
    REQUIRE( k4.testGetRoot()->key == "3" );
    REQUIRE( k4.getLevel("3") == 3 );
    REQUIRE( (getShape(k4.testGetRoot()).left == 2 && getShape(k4.testGetRoot()).right == 2) );
    REQUIRE( k4.testGetRoot()->right->key == "4" );
    REQUIRE( k4.testGetRoot()->left->key == "2" );
    k4.remove("2");
    REQUIRE( (getShape(k4.testGetRoot()).left == 2 && getShape(k4.testGetRoot()).right == 1) );
}

TEST_CASE("removeRebalanceCase3", "[Actual]")
{
    CrumpleTree<unsigned, unsigned> k1;
    std::vector<unsigned> tmp = {5,10,15,20,25};
    for(auto num : tmp)
    {
        k1.insert(num,num);
    }
    REQUIRE( k1.getLevel(10) == 3 );
    REQUIRE( k1.getLevel(20) == 2 );
    REQUIRE( k1.getLevel(5) == 1 );
    REQUIRE( k1.getLevel(15) == 1 );
    REQUIRE( k1.getLevel(25) == 1 );
    k1.remove(5);
    REQUIRE( k1.getLevel(10) == 2 );
    REQUIRE( k1.getLevel(20) == 3 );
    REQUIRE_THROWS_AS( k1.getLevel(5), ElementNotFoundException );
    REQUIRE( k1.getLevel(15) == 1 );
    REQUIRE( k1.getLevel(25) == 1 );

    CrumpleTree<unsigned, std::string> k2;
    for(auto num : tmp)
    {
        k2.insert(num,"");
    }
    Node<unsigned, std::string>* parent = new Node<unsigned, std::string>(30,"30",4);
    Node<unsigned, std::string>* right = new Node<unsigned, std::string>(35,"35",3);
    parent->right = right;
    parent->left = k2.testGetRoot();
    k2.testGetRoot()->parent = parent;
    k2.testGetRoot() = parent;
    REQUIRE( k2.getLevel(30) == 4 );
    REQUIRE( k2.getLevel(10) == 3 );
    REQUIRE( k2.getLevel(20) == 2 );
    REQUIRE( k2.getLevel(5) == 1 );
    REQUIRE( k2.getLevel(15) == 1 );
    REQUIRE( k2.getLevel(25) == 1 );
    k2.remove(5);
    REQUIRE( k2.getLevel(30) == 4 );
    REQUIRE( k2.testGetRoot()->left->key == 20 );
    REQUIRE( k2.getLevel(10) == 2 );
    REQUIRE( k2.getLevel(20) == 3 );
    REQUIRE_THROWS_AS( k2.getLevel(5), ElementNotFoundException );
    REQUIRE( k2.getLevel(15) == 1 );
    REQUIRE( k2.getLevel(25) == 1 );

    CrumpleTree<std::string, unsigned> k3;
    std::vector<std::string> tmp2 = {"y","t","o","j","e"};
    for(auto num : tmp2)
    {
        k3.insert(num,0);
    }
    REQUIRE( k3.getLevel("j") == 2 );
    REQUIRE( k3.getLevel("t") == 3 );
    REQUIRE( k3.getLevel("e") == 1 );
    REQUIRE( k3.getLevel("o") == 1 );
    REQUIRE( k3.getLevel("y") == 1 );
    k3.remove("e");
    REQUIRE( k3.getLevel("j") == 2 );
    REQUIRE( k3.getLevel("t") == 3 );
    REQUIRE_THROWS_AS( k3.getLevel("e"), ElementNotFoundException );
    REQUIRE( k3.getLevel("o") == 1 );
    REQUIRE( k3.getLevel("y") == 1 );

    CrumpleTree<std::string, std::string> k4;
    for(auto num : tmp2)
    {
        k4.insert(num,"");
    }
    REQUIRE( k4.getLevel("j") == 2 );
    REQUIRE( k4.getLevel("t") == 3 );
    REQUIRE( k4.getLevel("e") == 1 );
    REQUIRE( k4.getLevel("o") == 1 );
    REQUIRE( k4.getLevel("y") == 1 );
    k4.remove("e");
    REQUIRE( k4.getLevel("j") == 2 );
    REQUIRE( k4.getLevel("t") == 3 );
    REQUIRE_THROWS_AS( k4.getLevel("e"), ElementNotFoundException );
    REQUIRE( k4.getLevel("o") == 1 );
    REQUIRE( k4.getLevel("y") == 1 );
}

TEST_CASE("removeRebalanceCase4A", "[Actual]")
{
    Node<unsigned, unsigned>* ten = new Node<unsigned, unsigned>(10,10,4);
    Node<unsigned, unsigned>* five = new Node<unsigned, unsigned>(5,5,2,ten);
    ten->left = five;
    Node<unsigned, unsigned>* fifteen = new Node<unsigned, unsigned>(15,15,3,ten);
    ten->right = fifteen;
    Node<unsigned, unsigned>* eighteen = new Node<unsigned, unsigned>(18,18,2,fifteen);
    fifteen->right = eighteen;
    Node<unsigned, unsigned>* twelve = new Node<unsigned, unsigned>(12,12,1,fifteen);
    fifteen->left = twelve;
    Node<unsigned, unsigned>* two = new Node<unsigned, unsigned>(2,2,1,five);
    five->left = two;
    Node<unsigned, unsigned>* twenty = new Node<unsigned, unsigned>(20,20,1,eighteen);
    eighteen->right = twenty;
    CrumpleTree<unsigned, unsigned> k1;
    k1.testGetRoot() = ten;
    k1.setNumKeys(7);
    k1.remove(2);
    REQUIRE( k1.getLevel(15) == 4 );
    REQUIRE( k1.getLevel(10) == 3 );
    REQUIRE( k1.getLevel(18) == 2 );
    REQUIRE( k1.getLevel(5) == 1 );
    REQUIRE( k1.getLevel(12) == 1 );
    REQUIRE( k1.getLevel(20) == 1 );
}

TEST_CASE("removeRebalanceCase4B", "[Actual]")
{
    CrumpleTree<unsigned, unsigned> k1;
    std::vector<unsigned> tmp = {0,2,3,4,5};
    for(auto num : tmp)
    {
        k1.insert(num,num);
    }
    k1.remove(3);
    k1.remove(0);
    REQUIRE( k1.getLevel(4) == 2 );
    REQUIRE( k1.getLevel(2) == 1 );
    REQUIRE( k1.getLevel(5) == 1 );
    REQUIRE_THROWS_AS( k1.getLevel(3),ElementNotFoundException );
    REQUIRE_THROWS_AS( k1.getLevel(0),ElementNotFoundException );
    REQUIRE( k1.testGetRoot()->key == 4 );
    REQUIRE( (getShape(k1.testGetRoot()).left == 1 && getShape(k1.testGetRoot()).right == 1) );
    REQUIRE( k1.testGetRoot()->right->parent->key == 4 );
    REQUIRE( k1.testGetRoot()->left->parent->key == 4 );

    CrumpleTree<unsigned, std::string> k2;
    for(auto num : tmp)
    {
        k2.insert(num,"");
    }
    k2.remove(3);
    k2.remove(0);
    REQUIRE( k2.getLevel(4) == 2 );
    REQUIRE( k2.getLevel(2) == 1 );
    REQUIRE( k2.getLevel(5) == 1 );
    REQUIRE_THROWS_AS( k2.getLevel(3),ElementNotFoundException );
    REQUIRE_THROWS_AS( k2.getLevel(0),ElementNotFoundException );
    REQUIRE( k2.testGetRoot()->key == 4 );
    REQUIRE( (getShape(k2.testGetRoot()).left == 1 && getShape(k2.testGetRoot()).right == 1) );
    REQUIRE( k2.testGetRoot()->right->parent->key == 4 );
    REQUIRE( k2.testGetRoot()->left->parent->key == 4 );

    CrumpleTree<std::string, std::string> k3;
    std::vector<std::string> tmp2 = {"e","d","c","b","a"};
    for(auto num : tmp2)
    {
        k3.insert(num,"");
    }
    k3.remove("c");
    k3.remove("e");
    REQUIRE( k3.getLevel("b") == 2 );
    REQUIRE( k3.getLevel("a") == 1 );
    REQUIRE( k3.getLevel("d") == 1 );
    REQUIRE_THROWS_AS( k3.getLevel("c"),ElementNotFoundException );
    REQUIRE_THROWS_AS( k3.getLevel("e"),ElementNotFoundException );
    REQUIRE( k3.testGetRoot()->key == "b" );
    REQUIRE( (getShape(k3.testGetRoot()).left == 1 && getShape(k3.testGetRoot()).right == 1) );
    REQUIRE( k3.testGetRoot()->right->parent->key == "b" );
    REQUIRE( k3.testGetRoot()->left->parent->key == "b" );
    REQUIRE( k3.testGetRoot()->left->key == "a" );
    REQUIRE( k3.testGetRoot()->right->key == "d" );

    CrumpleTree<std::string, unsigned> k4;
    for(auto num : tmp2)
    {
        k4.insert(num,0);
    }
    k4.remove("c");
    k4.remove("e");
    REQUIRE( k4.getLevel("b") == 2 );
    REQUIRE( k4.getLevel("a") == 1 );
    REQUIRE( k4.getLevel("d") == 1 );
    REQUIRE_THROWS_AS( k4.getLevel("c"),ElementNotFoundException );
    REQUIRE_THROWS_AS( k4.getLevel("e"),ElementNotFoundException );
    REQUIRE( k4.testGetRoot()->key == "b" );
    REQUIRE( (getShape(k4.testGetRoot()).left == 1 && getShape(k4.testGetRoot()).right == 1) );
    REQUIRE( k4.testGetRoot()->right->parent->key == "b" );
    REQUIRE( k4.testGetRoot()->left->parent->key == "b" );
    REQUIRE( k4.testGetRoot()->left->key == "a" );
    REQUIRE( k4.testGetRoot()->right->key == "d" );
}

TEST_CASE("removeBalanceCase5", "[Actual]")
{
    CrumpleTree<unsigned, unsigned> k1;
    std::vector<unsigned> tmp = {4,3,8,9,2,6,7,5};
    for(auto num : tmp)
    {
        k1.insert(num,num);
    }
    REQUIRE( k1.getLevel(4) == 4 );
    REQUIRE( k1.getLevel(8) == 3 );
    REQUIRE( k1.getLevel(3) == 2 );
    REQUIRE( k1.getLevel(6) == 2 );
    REQUIRE( k1.getLevel(2) == 1 );
    REQUIRE( k1.getLevel(5) == 1 );
    REQUIRE( k1.getLevel(7) == 1 );
    REQUIRE( k1.getLevel(9) == 1 );
    k1.remove(2);
    REQUIRE( k1.getLevel(6) == 4 );
    REQUIRE( k1.getLevel(4) == 2 );
    REQUIRE( k1.getLevel(8) == 2 );
    REQUIRE( k1.getLevel(3) == 1 );
    REQUIRE( k1.getLevel(5) == 1 );
    REQUIRE( k1.getLevel(7) == 1 );
    REQUIRE( k1.getLevel(9) == 1 );
    REQUIRE( k1.testFindKey(3)->parent->key == 4 );
    REQUIRE( k1.testFindKey(4)->parent->key == 6 );
    REQUIRE( k1.testFindKey(5)->parent->key == 4 );
    REQUIRE( k1.testFindKey(8)->parent->key == 6 );
    REQUIRE( k1.testFindKey(7)->parent->key == 8 );
    REQUIRE( k1.testFindKey(9)->parent->key == 8 );
    REQUIRE( isLeafNode(k1.testFindKey(3)) );
    REQUIRE( isLeafNode(k1.testFindKey(5)) );
    REQUIRE( isLeafNode(k1.testFindKey(7)) );
    REQUIRE( isLeafNode(k1.testFindKey(9)) );
    REQUIRE( (k1.testFindKey(4)->left->key == 3 && k1.testFindKey(4)->right->key == 5) );
    REQUIRE( (k1.testFindKey(8)->left->key == 7 && k1.testFindKey(8)->right->key == 9) );
    REQUIRE( k1.testGetRoot()->key == 6 );
    REQUIRE( (k1.testGetRoot()->left->key == 4 && k1.testGetRoot()->right->key == 8) );
    REQUIRE( k1.testGetRoot()->parent == nullptr );

    CrumpleTree<unsigned, std::string> k2;
    for(auto num : tmp)
    {
        k2.insert(num,"num");
    }
    k2.remove(3);
    REQUIRE_THROWS_AS( k2.getLevel(3), ElementNotFoundException );
    REQUIRE( k2.getLevel(5) == 1 );

    CrumpleTree<std::string, unsigned> k3;
    std::vector<std::string> tmp2 = {"c","b","g","h","a","e","f","d"};
    for(auto num : tmp2)
    {
        k3.insert(num,0);
    }
    Node<std::string, unsigned>* z = new Node<std::string, unsigned>("z",0,5);
    Node<std::string, unsigned>* zz = new Node<std::string, unsigned>("zz",0,4,z);
    z->right = zz;
    k3.testGetRoot()->parent = z;
    z->left = k3.testGetRoot();
    k3.remove("a");
    REQUIRE( k3.getLevel("c") == 2 );
    REQUIRE( k3.getLevel("e") == 4 );
    REQUIRE( k3.testGetRoot()->key == "z");
    REQUIRE( k3.testGetRoot()->right->key == "zz");
    REQUIRE( k3.testGetRoot()->left->key == "e");

    CrumpleTree<std::string, std::string> k4;
    for(auto num : tmp2)
    {
        k4.insert(num,"0");
    }
    k4.remove("a");
    REQUIRE( k4.getLevel("c") == 2 );
}

TEST_CASE("removeBalanceCase6", "[Actual]")
{
    CrumpleTree<unsigned, unsigned> k1;
    std::vector<unsigned> tmp = {10,5,15,2,11,18,19,13};
    for(auto num : tmp)
    {
        k1.insert(num, num);
    }
    REQUIRE( k1.size() == 8 );
    REQUIRE( k1.getLevel(10) == 4 );
    REQUIRE( k1.getLevel(15) == 3 );
    REQUIRE( k1.getLevel(5) == 2 );
    REQUIRE( k1.getLevel(11) == 2 );
    REQUIRE( k1.getLevel(18) == 2 );
    REQUIRE( k1.getLevel(2) == 1 );
    REQUIRE( k1.getLevel(13) == 1 );
    REQUIRE( k1.getLevel(19) == 1 );

    k1.remove(11);
    k1.remove(18);
    REQUIRE( k1.getLevel(13) == 1 );
    REQUIRE( k1.getLevel(19) == 1 );
    REQUIRE( k1.testFindKey(15)->left->key == 13 );
    REQUIRE( k1.testFindKey(15)->right->key == 19 );
    REQUIRE( (getShape(k1.testFindKey(15)).left == 2 && getShape(k1.testFindKey(15)).right == 2) );
    k1.remove(2);
    REQUIRE( k1.getLevel(5) == 1 );
    REQUIRE( k1.getLevel(10) == 3 );
    REQUIRE( k1.getLevel(15) == 2 );

    CrumpleTree<unsigned, std::string> k2;
    for(auto num : tmp)
    {
        k2.insert(num, "num");
    }
    k2.remove(11);
    k2.remove(18);
    k2.remove(2);
    REQUIRE( k2.getLevel(5) == 1 );
    REQUIRE( k2.getLevel(10) == 3 );
    REQUIRE( k2.getLevel(15) == 2 );

    CrumpleTree<std::string, unsigned> k3;
    std::vector<std::string> tmp2 = {"j","e","o","b","k","r","s","m"};
    for(auto num : tmp2)
    {
        k3.insert(num, 0);
    }
    k3.remove("k");
    k3.remove("r");
    k3.remove("b");
    REQUIRE( k3.getLevel("j") == 3 );
    REQUIRE( k3.getLevel("o") == 2 );
    REQUIRE( k3.getLevel("e") == 1 );
    REQUIRE( k3.getLevel("m") == 1 );
    REQUIRE( k3.getLevel("s") == 1 );

    CrumpleTree<std::string, std::string> k4;
    for(auto num : tmp2)
    {
        k4.insert(num, "");
    }
    k4.remove("k");
    k4.remove("r");
    k4.remove("b");
    REQUIRE( k4.getLevel("j") == 3 );
    REQUIRE( k4.getLevel("o") == 2 );
    REQUIRE( k4.getLevel("e") == 1 );
    REQUIRE( k4.getLevel("m") == 1 );
    REQUIRE( k4.getLevel("s") == 1 );
}

TEST_CASE("sanityChecker", "[Helper]")
{
    CrumpleTree<int, std::string> tree;
    tree.insert(20, "are");
    tree.insert(19, "you");
    tree.insert(18, "following");
    tree.insert(12, "from");
    tree.insert(9, "lecture?");
    tree.remove(9);
    tree.remove(18);
    REQUIRE( crumpleTreeChecker(tree) );
}

TEST_CASE("bigSanityChecker", "[Helper]")
{
    CrumpleTree<unsigned, std::string> tree;
    for(unsigned i = 0; i < 100000; ++i)
    {
        REQUIRE( tree.size() == i );
        tree.insert(i, "");
    }
    for(unsigned i = 0; i < 100000; ++i)
    {
        REQUIRE( tree.size() == (100000-i) );
        tree.remove(i);
    }
    REQUIRE( crumpleTreeChecker(tree) );
}

} // end namespace