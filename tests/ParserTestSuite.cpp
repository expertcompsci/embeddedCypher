/*
BSD 3-Clause License

Copyright (c) 2017, expertcompsci
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of the copyright holder nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include <gtest/gtest.h>
#include "Parser.h"

class ParserTestSuite : public testing::Test {
protected:
    std::ostringstream oss;
    std::istringstream iss;

    void SetUp() {
    }

    void TearDown() {
        Parser parser(iss, oss);
        ASSERT_EQ(parser.parse(), 0);
        std::cout << oss.str();
    }

};
// Single node
TEST_F(ParserTestSuite, matchEmptyNodeSpec) {
    iss.str("MATCH () RETURN *");
}
TEST_F(ParserTestSuite, matchVarAndSingleLabelNodeSpec) {
    iss.str("MATCH (p:labelone:labeltwo) RETURN p");
}
TEST_F(ParserTestSuite, matchNameLabelProperty) {
    iss.str("MATCH (p:labelone { name:'value' }) RETURN p");
}
TEST_F(ParserTestSuite, matchNameLabelsProperty) {
    iss.str("MATCH (p:labelone:labeltwo { name:'value' }) RETURN p");
}
TEST_F(ParserTestSuite, matchVarEQNode) {
    iss.str("MATCH p = () RETURN p");
}
TEST_F(ParserTestSuite, matchVarEQNodeName) {
    iss.str("MATCH p = (x) RETURN p");
}
TEST_F(ParserTestSuite, matchVarEQNameLabel) {
    iss.str("MATCH p = (x:labelone) RETURN p");
}
TEST_F(ParserTestSuite, matchVarEQNameLabels) {
    iss.str("MATCH p = (x:labelone:labeltwo) RETURN p");
}
TEST_F(ParserTestSuite, matchVarEQNameLabelsProperty) {
    iss.str("MATCH p = (x:labelone:labeltwo { name:'value' }) RETURN p");
}
// Miscelaneous (never write openCypher like this!)
TEST_F(ParserTestSuite, miscOne) {
    iss.str(R"(
    MATCH ( ) -
[] -
     > 
    ( p : 
        labelone 
        : labeltwo )
    RETURN p
    )");
}
TEST_F(ParserTestSuite, miscTwo) {
    iss.str(R"(
    MATCH ( ) -
[] -
( p : 
        labelone 
        : labeltwo )
    RETURN p
    )");
}
// Multiple walks
TEST_F(ParserTestSuite, multiOne) {
    iss.str("MATCH ()--()-->()<--() RETURN *");
}

// Relationships node name
TEST_F(ParserTestSuite, matchRel) {
    iss.str("MATCH ()--() RETURN *");
}
TEST_F(ParserTestSuite, matchRelLeftNodeName) {
    iss.str("MATCH (p)--() RETURN *");
}
TEST_F(ParserTestSuite, matchRelRightNodeName) {
    iss.str("MATCH ()--(p) RETURN *");
}
TEST_F(ParserTestSuite, matchRightRel) {
    iss.str("MATCH ()-->() RETURN *");
}
TEST_F(ParserTestSuite, matchRightRelLeftNodeName) {
    iss.str("MATCH (p)-->() RETURN *");
}
TEST_F(ParserTestSuite, matchRightRelRightNodeName) {
    iss.str("MATCH ()-->(p) RETURN *");
}
TEST_F(ParserTestSuite, matchLeftRel) {
    iss.str("MATCH ()<--() RETURN *");
}
TEST_F(ParserTestSuite, matchLeftRelLeftNodeName) {
    iss.str("MATCH (p)<--() RETURN *");
}
TEST_F(ParserTestSuite, matchLeftRelRightNodeName) {
    iss.str("MATCH ()<--(p) RETURN *");
}
// Relationships node name and label
TEST_F(ParserTestSuite, matchRightRelLeftNodeNameLabel) {
    iss.str("MATCH (p:labelone)-->() RETURN *");
}
TEST_F(ParserTestSuite, matchRightRelRightNodeNameLabel) {
    iss.str("MATCH ()-->(p:labelone) RETURN *");
}
TEST_F(ParserTestSuite, matchLeftRelLeftNodeNameLabel) {
    iss.str("MATCH (p:labelone)<--() RETURN *");
}
TEST_F(ParserTestSuite, matchLeftRelRightNodeNameLabel) {
    iss.str("MATCH ()<--(p:labelone) RETURN *");
}
// Relationship mulitiple nodes name and label
TEST_F(ParserTestSuite, matchRelBothNodesNameLabel) {
    iss.str("MATCH (p:labelone)--(x:labeltwo) RETURN *");
}
TEST_F(ParserTestSuite, matchRightRelBothNodesNameLabel) {
    iss.str("MATCH (p:labelone)-->(x:labeltwo) RETURN *");
}
TEST_F(ParserTestSuite, matchLeftRelBothNodesNameLabel) {
    iss.str("MATCH (p:labelone)<--(x:labeltwo) RETURN *");
}
// Relationship details undirected
TEST_F(ParserTestSuite, matchRelDetail) {
    iss.str("MATCH ()-[]-() RETURN *");
}
TEST_F(ParserTestSuite, matchRelDetailLeftNodeName) {
    iss.str("MATCH (p)-[]-() RETURN *");
}
TEST_F(ParserTestSuite, matchRelDetailLeftNodeNameLabel) {
    iss.str("MATCH (p:labelone)-[]-() RETURN *");
}
TEST_F(ParserTestSuite, matchRelDetailLabel) {
    iss.str("MATCH ()-[:R]-() RETURN *");
}
TEST_F(ParserTestSuite, matchRelDetailLabelLeftNodeName) {
    iss.str("MATCH (p)-[:R]-() RETURN *");
}
TEST_F(ParserTestSuite, matchRelDetailLabelLeftNodeNameLabel) {
    iss.str("MATCH (p:labelone)-[:R]-() RETURN *");
}
TEST_F(ParserTestSuite, matchRelDetailLabelRightNodeName) {
    iss.str("MATCH ()-[:R]-(x) RETURN *");
}
TEST_F(ParserTestSuite, matchRelDetailLabelRightNodeNameLabel) {
    iss.str("MATCH ()-[:R]-(x:labelone) RETURN *");
}
TEST_F(ParserTestSuite, matchRelDetailLabelLeftNodeNameRightNodeNameLabel) {
    iss.str("MATCH (p)-[:R]-(x:labelone) RETURN *");
}
TEST_F(ParserTestSuite, matchRelDetailLabelLeftNodeNameLabelRightNodeNameLabel) {
    iss.str("MATCH (p:labeltwo)-[:R]-(x:labelone) RETURN *");
}
// Relationship details right
TEST_F(ParserTestSuite, matchRightRelDetail) {
    iss.str("MATCH ()-[]->() RETURN *");
}
TEST_F(ParserTestSuite, matchRightRelDetailLeftNodeName) {
    iss.str("MATCH (p)-[]->() RETURN *");
}
TEST_F(ParserTestSuite, matchRightRelDetailLeftNodeNameLabel) {
    iss.str("MATCH (p:labelone)-[]->() RETURN *");
}
TEST_F(ParserTestSuite, matchRightRelDetailLabel) {
    iss.str("MATCH ()-[:R]->() RETURN *");
}
TEST_F(ParserTestSuite, matchRightRelDetailLabelLeftNodeName) {
    iss.str("MATCH (p)-[:R]->() RETURN *");
}
TEST_F(ParserTestSuite, matchRightRelDetailLabelLeftNodeNameLabel) {
    iss.str("MATCH (p:labelone)-[:R]->() RETURN *");
}
TEST_F(ParserTestSuite, matchRightRelDetailLabelRightNodeName) {
    iss.str("MATCH ()-[:R]->(x) RETURN *");
}
TEST_F(ParserTestSuite, matchRightRelDetailLabelRightNodeNameLabel) {
    iss.str("MATCH ()-[:R]->(x:labelone) RETURN *");
}
TEST_F(ParserTestSuite, matchRightRelDetailLabelLeftNodeNameRightNodeNameLabel) {
    iss.str("MATCH (p)-[:R]->(x:labelone) RETURN *");
}
TEST_F(ParserTestSuite, matchRightRelDetailLabelLeftNodeNameLabelRightNodeNameLabel) {
    iss.str("MATCH (p:labeltwo)-[:R]->(x:labelone) RETURN *");
}
// Relationship details left
TEST_F(ParserTestSuite, matchLeftRelDetail) {
    iss.str("MATCH ()<-[]-() RETURN *");
}
TEST_F(ParserTestSuite, matchLeftRelDetailLeftNodeName) {
    iss.str("MATCH (p)<-[]-() RETURN *");
}
TEST_F(ParserTestSuite, matchLeftRelDetailLeftNodeNameLabel) {
    iss.str("MATCH (p:labelone)<-[]-() RETURN *");
}
TEST_F(ParserTestSuite, matchLeftRelDetailLabel) {
    iss.str("MATCH ()<-[:R]-() RETURN *");
}
TEST_F(ParserTestSuite, matchLeftRelDetailLabelLeftNodeName) {
    iss.str("MATCH (p)<-[:R]-() RETURN *");
}
TEST_F(ParserTestSuite, matchLeftRelDetailLabelLeftNodeNameLabel) {
    iss.str("MATCH (p:labelone)<-[:R]-() RETURN *");
}
TEST_F(ParserTestSuite, matchLeftRelDetailLabelRightNodeName) {
    iss.str("MATCH ()<-[:R]-(x) RETURN *");
}
TEST_F(ParserTestSuite, matchLeftRelDetailLabelRightNodeNameLabel) {
    iss.str("MATCH ()<-[:R]-(x:labelone) RETURN *");
}
TEST_F(ParserTestSuite, matchLeftRelDetailLabelLeftNodeNameRightNodeNameLabel) {
    iss.str("MATCH (p)<-[:R]-(x:labelone) RETURN *");
}
TEST_F(ParserTestSuite, matchLeftRelDetailLabelLeftNodeNameLabelRightNodeNameLabel) {
    iss.str("MATCH (p:labeltwo)<-[:R]-(x:labelone) RETURN *");
}
// Relationships label or label query undirected
TEST_F(ParserTestSuite, matchRelOrLabel) {
    iss.str("MATCH ()-[:R | S]-() RETURN *");
}
TEST_F(ParserTestSuite, matchRelOrLabelLeftNodeName) {
    iss.str("MATCH (p)-[:R | S]-() RETURN *");
}
TEST_F(ParserTestSuite, matchRelOrLabelLeftNodeNameLabel) {
    iss.str("MATCH (p:labelone)-[:R | S]-() RETURN *");
}
TEST_F(ParserTestSuite, matchRelOrLabelRightNodeName) {
    iss.str("MATCH ()-[:R | S]-(x) RETURN *");
}
TEST_F(ParserTestSuite, matchRelOrLabelRightNodeNameLabel) {
    iss.str("MATCH ()-[:R | S]-(x:labelone) RETURN *");
}
TEST_F(ParserTestSuite, matchRelOrLabelLeftNodeNameRightNodeNameLabel) {
    iss.str("MATCH (p)-[:R | S]-(x:labelone) RETURN *");
}
TEST_F(ParserTestSuite, matchRelOrLabelLeftNodeNameLabelRightNodeNameLabel) {
    iss.str("MATCH (p:labeltwo)-[:R | S]-(x:labelone) RETURN *");
}
// Relationships right label or label query undirected
TEST_F(ParserTestSuite, matchRightRelOrLabel) {
    iss.str("MATCH ()-[:R | S]->() RETURN *");
}
TEST_F(ParserTestSuite, matchRightRelOrLabelLeftNodeName) {
    iss.str("MATCH (p)-[:R | S]->() RETURN *");
}
TEST_F(ParserTestSuite, matchRightRelOrLabelLeftNodeNameLabel) {
    iss.str("MATCH (p:labelone)-[:R | S]->() RETURN *");
}
TEST_F(ParserTestSuite, matchRightRelOrLabelRightNodeName) {
    iss.str("MATCH ()-[:R | S]->(x) RETURN *");
}
TEST_F(ParserTestSuite, matchRightRelOrLabelRightNodeNameLabel) {
    iss.str("MATCH ()-[:R | S]->(x:labelone) RETURN *");
}
TEST_F(ParserTestSuite, matchRightRelOrLabelLeftNodeNameRightNodeNameLabel) {
    iss.str("MATCH (p)-[:R | S]->(x:labelone) RETURN *");
}
TEST_F(ParserTestSuite, matchRightRelOrLabelLeftNodeNameLabelRightNodeNameLabel) {
    iss.str("MATCH (p:labeltwo)-[:R | S]->(x:labelone) RETURN *");
}
// Relationships left label or label query undirected
TEST_F(ParserTestSuite, matchLeftRelOrLabel) {
    iss.str("MATCH ()<-[:R | S]-() RETURN *");
}
TEST_F(ParserTestSuite, matchLeftRelOrLabelLeftNodeName) {
    iss.str("MATCH (p)<-[:R | S]-() RETURN *");
}
TEST_F(ParserTestSuite, matchLeftRelOrLabelLeftNodeNameLabel) {
    iss.str("MATCH (p:labelone)<-[:R | S]-() RETURN *");
}
TEST_F(ParserTestSuite, matchLeftRelOrLabelRightNodeName) {
    iss.str("MATCH ()<-[:R | S]-(x) RETURN *");
}
TEST_F(ParserTestSuite, matchLeftRelOrLabelRightNodeNameLabel) {
    iss.str("MATCH ()<-[:R | S]-(x:labelone) RETURN *");
}
TEST_F(ParserTestSuite, matchLeftRelOrLabelLeftNodeNameRightNodeNameLabel) {
    iss.str("MATCH (p)<-[:R | S]-(x:labelone) RETURN *");
}
TEST_F(ParserTestSuite, matchLeftRelOrLabelLeftNodeNameLabelRightNodeNameLabel) {
    iss.str("MATCH (p:labeltwo)<-[:R | S]-(x:labelone) RETURN *");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
