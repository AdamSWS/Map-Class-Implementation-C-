// tests.cpp
//
// Adam Shaar
// tests.cpp tests each milestone in mymap.h

#include "gtest/gtest.h"
#include "mymap.h"
#include "myrandom.h"
#include <map>

TEST(mymap, Milestone1_Double) {
    // test to compare with C++ map
    mymap<double, double> mapMine;
    map<double, double> mapSol;
    int n = 1000000;  // # of elements inserted
    // fill up BOTH maps
    for (int i = 1; i <= n; i++) {
        double key = randomInteger(0,10000);  // given
        double val = randomInteger(0,10000);
        mapMine.put(key, val);
        mapSol[key] = val;
    }
    // 1. Assert sizes are equal
    EXPECT_EQ(mapMine.Size(), mapSol.size());
    // 2. String test (order is correct)
    stringstream solution("");
    // Fill string stream with mapSol
    for (auto e : mapSol) {
        solution << "key: " << e.first;
        solution << " value: " << e.second << endl;
        // 3. Test map contents
        EXPECT_TRUE(mapMine.contains(e.first));
        EXPECT_EQ(mapMine.get(e.first), e.second);
    }
    EXPECT_EQ(mapMine.toString(), solution.str());
}

TEST(mymap, Milestone1_INT) {
    // test to compare with C++ map
    mymap<int, int> mapMine;
    map<int, int> mapSol;
    int n = 1000000;  // # of elements inserted
    // fill up BOTH maps
    for (int i = 1; i <= n; i++) {
        int key = randomInteger(0,10000);  // given
        int val = randomInteger(0,10000);
        mapMine.put(key, val);
        mapSol[key] = val;
    }
    // 1. Assert sizes are equal
    EXPECT_EQ(mapMine.Size(), mapSol.size());
    // 2. String test (order is correct)
    stringstream solution("");
    // Fill string stream with mapSol
    for (auto e : mapSol) {
        solution << "key: " << e.first;
        solution << " value: " << e.second << endl;
        // 3. Test map contents
        EXPECT_TRUE(mapMine.contains(e.first));
        EXPECT_EQ(mapMine.get(e.first), e.second);
    }
    EXPECT_EQ(mapMine.toString(), solution.str());
}

TEST(mymap, Milestone1_CHAR) {
    // test to compare with C++ map
    mymap<int, char> mapMine;
    map<int,char> mapSol;
    int n = 1000000;  // # of elements inserted
    // fill up BOTH maps
    for (int i = 1; i <= n; i++) {
        int key = randomInteger(0,10000);  // given
        int val = randomInteger(0,10000);
        char cVal  = (val % 26) + 'a'  ;
        mapMine.put(key, cVal);
        if(mapSol.count(key)){ mapSol.at(key) = cVal ; }
        else {
            mapSol.emplace(key, cVal);
        }
    }

    // 1. Assert sizes are equal
    ASSERT_EQ(mapMine.Size(), mapSol.size());
    // 2. String test (order is correct)
    stringstream solution("");
    // Fill string stream with mapSol
    for (auto e : mapSol) {
        solution << "key: " << e.first;
        solution << " value: " << e.second << endl;
        // 3. Test map contents
        ASSERT_TRUE(mapMine.contains(e.first));
        ASSERT_EQ(mapMine.get(e.first), e.second);
    }
    ASSERT_EQ(mapMine.toString(), solution.str());

}

TEST(mymap, Milestone1_STR) {
    // test to compare with C++ map
    mymap<int, string> mapMine;
    map<int, string> mapSol;
    int n = 1000000;  // # of elements inserted
    int MAX_SIZE = 26 ;
    int stringSize = 10 ;
    char chars[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    // fill up BOTH maps
    for (int i = 1; i <= n; i++) {
        int key = randomInteger(0,10000);  // given
        int val = randomInteger(0,10000);
        string build = "";
        for(int i = 0 ; i < stringSize; i++) {
            build  = build + chars[val % 26] ;
        }
        mapMine.put(key, build);
        if(mapSol.count(key)){
            mapSol.at(key) = build;
        }
        else {
            mapSol.emplace(key, build);
        }
        build.clear();
    }
    // 1. Assert sizes are equal
    ASSERT_EQ(mapMine.Size(), mapSol.size());
    // 2. String test (order is correct)
    stringstream solution("");
    // Fill string stream with mapSol
    for (auto e : mapSol) {
        solution << "key: " << e.first;
        solution << " value: " << e.second << endl;
        // 3. Test map contents
        ASSERT_TRUE(mapMine.contains(e.first));
        ASSERT_EQ(mapMine.get(e.first), e.second);
    }
    ASSERT_EQ(mapMine.toString(), solution.str());
}

TEST (mymap, MS1AccessInt){
    mymap<int, int> testMe;
    map<int, int> correct;
    testMe.put(1, 1);
    correct.emplace(
            pair<int, int>(1, 1));
    // check if key exists:
    EXPECT_EQ(true,
          testMe.contains(1));
    // check the values:
    EXPECT_EQ(testMe.get(1),
              correct[1]);
    EXPECT_EQ(testMe[1],
              correct[1]);
    // try to make this test
    // repetitive using loops
}

TEST (mymap, MS1AccessDub){
    mymap<double, double> testMe;
    map<double, double> correct;
    testMe.put(1.3, 5673.2);
    correct.emplace(
            pair<double, double>(1.3, 5673.2));
    // check if key exists:
    EXPECT_EQ(true,
              testMe.contains(1.3));
    // check the values:
    EXPECT_EQ(testMe.get(1.3),
              correct[1.3]);
    EXPECT_EQ(testMe[1.3],
              correct[1.3]);
    // try to make this test
    // repetitive using loops
}

TEST (mymap, MS1AccessString){
    mymap<string, string> testMe;
    map<string, string> correct;
    testMe.put("Adam", "Program5");
    correct.emplace(
            pair<string, string>("Adam", "Program5"));
    // check if key exists:
    EXPECT_EQ(true,
              testMe.contains("Adam"));
    // check the values:
    EXPECT_EQ(testMe.get("Adam"),
              correct["Adam"]);
    EXPECT_EQ(testMe["Adam"],
              correct["Adam"]);
    // try to make this test
    // repetitive using loops
}

TEST (mymap, MS1SS) {
    mymap<int, int> test;
    stringstream dump;
    int n = 30;
    // add some values:
    for (int i = n; i > 0; i--) {
        // put values
        test.put(i, i);
        // build stringstream:
        dump << "key: " << i << " " << "value: " << i << "\n";
    }
    // test toString output
    ASSERT_EQ(dump.str(),
              test.toString());
}

TEST (mymap, putSAME) {
    mymap<int, int> test;
    test.put(1, 1);
    test.put(1, 2);
    EXPECT_EQ(test.get(1), 2);
}

TEST (mymap, clear){
    mymap<int,int> m;
    for (int i=0;i<1000;i++) {
        int x = randomInteger(0,10000);
        m.put(x, x);
        EXPECT_NE(m.Size(), 0);
    }
    m.clear();
    ASSERT_EQ(m.Size(), 0);
}

TEST (mymap, copy){
    mymap<int,int> m1;
    for (int i=0;i<1000;i++) {
        int x = randomInteger(0,10000);
        m1.put(x, x);
    }
    mymap<int,int> m2 = m1;
    ASSERT_EQ(m2.Size(), m1.Size());
    ASSERT_EQ(m2.toString(),
              m1.toString());
}

TEST (mymap, toVector){
    mymap<int,int> m;
    vector<pair<int,int>> v;
    int arr[] = {2,1,3};
    for (int i=0;i<3;i++) {
        m.put(arr[i], arr[i]);
        v.push_back(make_pair(i+1,i+1));
    }
    for (auto i = 0; i < v.size(); i++) {
        cout << v.at(i).first << endl;
    }
    ASSERT_EQ(m.toVector(), v);
}

TEST (mymap, checkBalance){
    mymap<int,int> m;
    string s = "";
    for (int i=0;i<3;i++) {
        m.put(i, i);
    }
    s += "key: 1, nL: 1, nR: 1\n";
    s += "key: 0, nL: 0, nR: 0\n";
    s += "key: 2, nL: 0, nR: 0\n";
    ASSERT_EQ(m.checkBalance(), s);
}




