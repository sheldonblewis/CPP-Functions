// how to compile:
// g++ -std=c++20 -Wall -fmodules-ts -xc++-system-header fstream
// g++ -std=c++20 -Wall -fmodules-ts -xc++-system-header iostream
// g++ -std=c++20 -Wall -fmodules-ts -xc++-system-header utility
// g++ -std=c++20 -Wall -fmodules-ts -xc++-system-header string
// g++ -std=c++20 -Wall -fmodules-ts -c BCode.cc
// g++ -std=c++20 -Wall -fmodules-ts -c BCode-impl.cc
// g++ -std=c++20 -Wall -fmodules-ts -c Building.cc
// g++ -std=c++20 -Wall -fmodules-ts -c Building-impl.cc
// g++ -std=c++20 -Wall -fmodules-ts -c Collection.cc
// g++ -std=c++20 -Wall -fmodules-ts -c Collection-impl.cc
// g++ -std=c++20 -Wall -fmodules-ts -c Graph.cc
// g++ -std=c++20 -Wall -fmodules-ts -c Graph-impl.cc
// g++ -std=c++20 -Wall -fmodules-ts -c main_building_graph_connection_map.cc

import <iostream>;
import <fstream>;
import <string>;
import bcode;
import building;
import collection;
import graph;
using namespace std;

//************************************************************************
//  Test Harness Helper functions
//************************************************************************

//  test-harness operators
enum Op { NONE, mapPtr, building, wreckage, findB, node, remNode, edge, remEdge, delGraph, 
    copyCtorGraph, moveCtorGraph, copyAssignGraph, moveAssignGraph, eq, path, print };

Op convertOp( const string& opStr ) {
    switch( opStr[0] ) {
        case 'm': return mapPtr;
        case 'b': return building;
        case 'w': return wreckage;
        case 'f': return findB;
        case 'n': return node;
        case 'v': return remNode;
        case 'e': return edge;
        case 'r': return remEdge;
        case 'd': return delGraph;
        case 'c': 
            {   if ( opStr.length() >= 2 && opStr[1] == 'c' )
                    return copyCtorGraph;
                if ( opStr.length() >= 2 && opStr[1] == 'm' )
                    return moveCtorGraph;
                return NONE;
            }
        case 'a': 
            {   if ( opStr.length() >= 2 && opStr[1] == 'c' )
                    return copyAssignGraph;
                if ( opStr.length() >= 2 && opStr[1] == 'm' )
                    return moveAssignGraph;
                return NONE;
            }
        case 'q': return eq;
        case 'p': return path;
        case 'g': return print;
        default: {
            return NONE;
        }
    } // switch
} // convert

//******************************************************************
// Test Harness for Graph ADT
// Input commands affect whichever graph that "map" points to (map1 or map2).
//******************************************************************

int main( int argc, char *argv[] ) {
    Collection buildings;
    Graph map1{"map1"}, map2{"map2"};
    Graph* map = &map1;  
    string command;

    // Initialize buildings and map1 with input file, if present.
    if ( argc > 1 ) {
     
        ifstream source{ argv[1] };
        if ( source.fail() ) {
            cerr << "Error: Couldn't open file \"" << argv[1] << "\"." << endl;
            return 1;
        } // if
    
        // Create a collection of buildings, and a map of buildings and their
        // links in map1.
        while ( source >> command ) {
            switch( convertOp( command ) ) {
                    
                // Add a new building to the collection of Buildings, and add
                // the building to map1.
                case building : {
                    string code;
                    string name;
                    string name2;
                    source >> code >> name;
                    getline( source, name2 );
                    name += name2;
                    buildings.insert( code, name );
                    map1.addNode( buildings.findBuilding( code ) );
                    break;
                }
                    
                // Add a new link between two existing nodes in map1.
                case edge: {
                    string code1, code2, type;
                    source >> code1 >> code2 >> type;
                    map1.addEdge( code1, code2, type );
                    string junk;
                    getline( source, junk );
                    break;
                }
                    
                default: { }
            } // switch
        } // while
    } // if
    
    cout << map1 << "Test harness for Graph ADT:\n" << endl;
        
    while ( cin >> command ) {
        switch( convertOp( command ) ) {

            // Set map to point to new graph (map1 or map2).
            case mapPtr: {
                string mapNo;
                cin >> mapNo;
                map = ( mapNo[0] == '1' ) ? &map1 : &map2;
                break;
            }
                
            // Print the current map to standard output.
            case print: {
                cout << *map;
                break;
            }
                
            // Add a new building to the collection of buildings.
            case building : {
                string code;
                string name;
                string name2;
                cin >> code >> name;
                getline( cin, name2 );
                name += name2;
                buildings.insert( code, name );
                break;
            }
                
            // Add an existing building to the current map.
            case node: {
                string code;
                cin >> code;
                Building *b = map->findBuilding( code );
                if ( b ) {
                    cout << "Building with code " << code 
                        << " is already in the map" << endl;
                } else {
                    b = buildings.findBuilding( code );
                    map->addNode( b );
                } // if
                string junk;
                getline( cin, junk );
                break;
            }
                
            // Find a building in the current map.
            case findB: {
                string code;
                cin >> code;
                Building *b = map->findBuilding( code );
                if ( b ) {
                    cout << *b << endl;
                } else {
                    cout << "Couldn't find building " << code << endl;
                } // if
                cout << endl;
                string junk;
                getline( cin, junk );
                break;
            }

            // Add a new link between existing graph nodes in the current map.
            case edge: {
                string code1, code2, type;
                cin >> code1 >> code2 >> type;
                map->addEdge( code1, code2, type );
                string junk;
                getline( cin, junk );
                break;
            }
                
                
            // Delete the entire graph. There should be no memory leak.
            // There is no change to the collection of Buildings.
            case delGraph: {
                map->deleteGraph();
                break;
            }

            // Remove an existing edge from the current map.
            case remEdge: {
                string code1, code2;
                cin >> code1 >> code2;
                map->removeEdge( code1, code2 );
                string junk;
                getline ( cin, junk );
                break;
            }
                
            // Remove an existing node from the current map. 
            // There is no change to the collection of Buildings.
            case remNode: {
                string code;
                cin >> code;
                map->removeNode( code );
                string junk;
                getline( cin, junk );
                break;
            }
            
            // Remove an existing building from the collection of buildings. 
            // The building also needs to be removed from the two maps, 
            // as well as all links involving the building.
            case wreckage: {
                string code;
                cin >> code;
                map1.removeNode( code );
                map2.removeNode( code );
                buildings.remove( code );
                string junk;
                getline( cin, junk );
                break;
            }

            // Check whether map1 is equal to map2
            case eq: {
                if ( map1 == map2 ) {
                    cout << "Maps 1 and 2 are equal." << endl;
                } else {
                    cout << "Maps 1 and 2 are NOT equal." << endl;
                } // if
                break;
            }
                
            // Test the graph copy constructor.
            case copyCtorGraph: {
                Graph map3{ *map };
                map3.setName( "map3" );
                cout << map3;
                string junk;
                getline( cin, junk );
                if ( map3 == *map ) {
                    cout << "map3 is a copy." << endl;
                } else {
                    cout << "map3 is NOT a copy." << endl;
                } // if

                // Add a building, add a node to map3, then check
                // equality again.
                buildings.insert( "ZZ1", "Nuclear Reactor Research Facility" );
                map->addNode( buildings.findBuilding( "ZZ1" ) );
                cout << *map;
                if ( map3 == *map ) {
                    cout << "map3 is a copy." << endl;
                } else {
                    cout << "map3 is NOT a copy." << endl;
                } // if     
                map->removeNode( "ZZ1" );           
                buildings.remove( "ZZ1" );
                break;
            }

            // Test graph move constructor.
            case moveCtorGraph: {
                Graph map3{ std::move( *map ) };
                map3.setName( "map3" );
                cout << map3 << *map << endl;

                if ( map3 == *map ) {
                    cout << "map3 is a copy." << endl;
                } else {
                    cout << "map3 is NOT a copy." << endl;
                } // if  
                string junk;
                getline( cin, junk );
                break;
            }
            
            // Test graph copy assignment operator.
            case copyAssignGraph: {
                map1 = map2;
                cout << map1;
                break;
            }

            // Test graph move assignment operator
            case moveAssignGraph: {
                map1 = std::move( map2 );
                cout << map1;
                break;
            }

            // Find path(s) in graph from one building to another building
            case path: {
                string code1, code2, all;
                cin >> code1 >> code2 >> all;
                cout << "Paths from " << code1 << " to " << code2 << " are: " << endl;
                bool printall = ( all.length() > 0 && all.at(0) == 't' ) ? true : false;
                map->printPaths( code1, code2, printall );
                string junk;
                getline( cin, junk );
                break;
            }
                
            default: {
                cerr << "Invalid command." << endl;
            }
        } // switch
        
    } // while
} // main
