#include "Robot.h"
/*
	Karel is a framework for manipulating with Karel the robot.
	Karel is a subclass of ROBOT from the library Robot.
	Last Modified:	September 16 2006, by Pieter Koopman, RU Nijmegen
	With some additions: September 12 2007, by Ger Paulussen & Peter Achten
	More additions: August 21 2013, by Peter Achten
*/

// added by student: Zaid Ajaj
#include <iostream>
#include <string>

using namespace std;

// =========================================================================

// Here are the examples that have been explained during the lecture
void take_3_steps ()
{
    step () ;
    step () ;
    step () ;
}

void swap_ball ()
{
    if (on_ball ())
        get_ball () ;
    else
	    put_ball () ;
    step () ;
}

// put_a_ball_somewhere adds a single ball to Charles' world on a random location
void put_a_ball_somewhere ()
{
    int lane   = 1 + rand () % (WereldHoogte  - 2) ;
    int street = 1 + rand () % (WereldBreedte - 2) ;
    create_ball (street, lane) ;
}

// make_church creates a Church-like shape of walls
void make_church ()
{
    place_rectangle (10,10,20,8) ;
    place_rectangle (10,18, 4,4) ;
    place_walls (12,22,4,false) ;
    place_walls (11,25,2,true) ;
}

// make_block creates an arbitrary block inside Charles' world and places a ball
// on the 'north' most lane at the 'west' most street corner.
void make_block ()
{
    const int left   = rand () % (WereldBreedte / 3) + 5;
    const int bottom = rand () % (WereldHoogte  / 4) + 5;
    const int width  = rand () % (WereldBreedte / 2) + 5;
    const int height = rand () % (WereldHoogte  / 2) + 2;
    place_rectangle (left,bottom,width,height) ;
    create_ball (left, WereldHoogte-2) ;
}
// turn_north makes Charles look north
void turn_north ()
{
    while (!north())
        turn_left();
}

void turn_around ()
{
    turn_left() ;
    turn_left() ;
}
// walk_to_wall makes Charles walk ahead and stop immediately before the wall
void walk_to_wall ()
{
    while (!in_front_of_wall())
        step () ;
}

// go_to_north_west_corner makes Charles move to north-west corner and look to the east
// it is assumed that that there are only the exterior walls
void go_to_north_west_corner ()
{
    turn_north() ;
    walk_to_wall() ;
    turn_left() ;
    walk_to_wall() ;
    turn_around() ;
}

// sweep_lane makes Charles walk ahead until it is on top of a ball or immediately before a wall
void sweep_lane ()
{
    while (!on_ball() && !in_front_of_wall())
        step () ;
}

// go_down_east_if_not_on_ball moves Charles one lane to the south if he is not on a ball.
// it is assumed that Charles is facing east and is not on the southernmost lane
void go_down_east_if_not_on_ball ()
{
    if (!on_ball())
    {
        turn_right() ;
        step() ;
        turn_right() ;
    }
}

// go_down_west_if_not_on_ball moves Charles one lane to the south if he is not on a ball.
// it is assumed that Charles is facing west and is not on the southernmost lane
void go_down_west_if_not_on_ball ()
{
    if (!on_ball())
    {
        turn_left () ;
        step () ;
        turn_left () ;
    }
}

// sweep_lanes makes Charles move to the east and find the ball, followed by
// going on lane south and moving to the west to find the ball.
// Assumptions: Charles is standing at the north-west corner and is looking east, there are only the exterior walls, and a ball is present.
// Result:      Charles is standing on the ball
void sweep_lanes ()
{
    while (!on_ball())
    {
        sweep_lane ();
        go_down_east_if_not_on_ball () ;
        sweep_lane () ;
        go_down_west_if_not_on_ball () ;
    }
}

// This example has been discussed during the lecture
// The effect of this function is that Charles will search for a ball in its universe.
// Assumptions: Charles is standing on its base position, there are only the exterior walls, and a ball is present.
// Result:      Charles is standing on the ball.
void find_ball ()
{
    sweep_lanes () ;
}

// here starts the part with code to be completed by the students

// Zaid Ajaj / 4807651 / Informatica & Wiskunde

void get_ball_safely()
{
    if (on_ball())
    {
        get_ball();
    }
}

void get_available_balls_until_faced_with_wall()
{
    while (!in_front_of_wall())
    {
        get_ball_safely();
        // move forward
        step();
    }
}

// give one or more comment lines about what will happen in this function
void clean_string_with_balls ()
{
	make_string_with_balls () ;
	// perform this block 4 times
    get_available_balls_until_faced_with_wall();
    turn_right();
    get_available_balls_until_faced_with_wall();
    turn_right();
    get_available_balls_until_faced_with_wall();
    turn_right();
    get_available_balls_until_faced_with_wall();
    turn_right();
}


void move_forward_until_facing_wall()
{
    while(!in_front_of_wall())
    {
        step();
    }
}

// helper function to go back to east wall when finished collecting walls
void back_to_east_wall()
{
    turn_around();
    move_forward_until_facing_wall();
}

// safely collect all available balls facing Charles in it's current row
void get_balls_until_none_available()
{
    while(on_ball())
    {
        get_ball();
        step();
    }
}

// move to the next line when you are back at the east wall
void next_line()
{
    turn_right();
    step();
    turn_right();
}
// give one or more lines about what will happen in this function
void clean_chaos_with_balls ()
{
    // generate balls
	make_chaos_with_balls () ;
    // initially, just go to the east wall
    move_forward_until_facing_wall();
    // turn around facing the balls to be collected
    turn_around();

    while(true)
    {
        // get all balls on current row
        get_balls_until_none_available();
        turn_around();
        // return to east wall
        move_forward_until_facing_wall();
        // move to next line
        next_line();

        // if the next line does not have a ball then we are finished
        if (!on_ball())
        {
            // go  back to initial position
            turn_right();
            move_forward_until_facing_wall();
            turn_left();
            move_forward_until_facing_wall();
            turn_around();
            return;
        }
    }
}

// this is the initial set-up for the tracing Charles assignment
void tracing_Charles ()
{
    reset () ;
    create_ball (WereldBreedte - 5, WereldHoogte - 3) ;
    steps (WereldBreedte - 5) ;
}

int put_balls_across_side()
{
    bool finishedSide = false;
    while(finishedSide == false)
    {
        turn_right();
        if (in_front_of_wall())
        {
            put_ball();
            turn_left();
            step();
        }
        else
        {
            put_ball();
            finishedSide = true;
        }
    }

    step();
}

// give one or more comment lines about what will happen in this function
void around_the_block ()
{
    make_block () ;
    while (!on_ball())
    {
        // keep moving until you find a ball
        step();
    }

    // turn right to face the generated block
    turn_right();
    // go to the block
    move_forward_until_facing_wall();
    turn_left();
    // place balls across the top side
    put_balls_across_side();
    // place balls across the right side
    put_balls_across_side();
    // place balls across the bottom side
    put_balls_across_side();
    // // place balls across the left side
    put_balls_across_side();
    // face the north wall
    turn_left();
    // go back to initial position
    move_forward_until_facing_wall();
    turn_left();
    move_forward_until_facing_wall();
    turn_around();
}


/*
    Zaid Ajaj:
    Here follows the answer of stack frames (snapshots) for Part 1.2 of the bonus assignment

    .OC.OX  <>
    .OC.OX  <4>
    .OC.OX  <4,false>
    .OC.OX  <4>
    .OC.OX  <>
    .OC.OX  <5>
    .OC.OX  <5,1>
    .OC.OX  <5,1,true>
    .OC.OX  <5,1>
    .OC.OX  <5>
    .OC.OX  <5,2>
    .Oc.OX  <5,2> 
    .Oc.OX  <5>
    .Oc.OX  <>
    .Oc.OX  <6>
    .O.cOX  <6>
    .O.cOX  <>
    .O.cOX  <4>
    .O.cOX  <4,false>
    .O.cOX  <4>
    .O.cOX  <>
    .O.cOX  <5>
    .O.cOX  <5,1>
    .O.cOX  <5,1,false>
    .O.cOX  <5,1>
    .O.cOX  <5>
    .O.cOX  <5,3>
    .O.COX  <5,3>
    .O.COX  <5>
    .O.COX  <>
    .O.COX  <6>
    .O.0CX  <6>
    .O.0CX  <4>
    .O.0CX  <4,true>
    .O.0CX  <4>
    .O.0CX  <>
*/

// Charles searches for the ball and remains there
void search_the_ball ()
{
	put_a_ball_somewhere () ;
	find_ball () ;
}

// For testing purposes, you can define your own function here:
void test ()
{
    // enter your Charles code here
}

// end of part with code to be completed by students
// =========================================================================


void quick  () { rest(    1); };
void normal () { rest(dInit); };
void slow   () { rest(  250); };
void very_slow  () { rest( 1000); };

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
    Menu charles_menu ((char*)"Charles") ;
    charles_menu.add ((char*)"Clean", reset)
                .add ((char*)"Stop",  stop) ;

	Menu l1_menu ((char*)"Examples Lecture 1");
	l1_menu.add ((char*)"Steps",take_3_steps)
	       .add ((char*)"Swap ball",swap_ball)
	       .add ((char*)"Find ball",search_the_ball);

	Menu a1_menu ((char*)"Assignment 1");
	a1_menu.add ((char*)"Balls: a string...", clean_string_with_balls )
		   .add ((char*)"Balls: chaos...", clean_chaos_with_balls )
		   .add ((char*)"Balls: tracing Charles...", tracing_Charles )
		   .add ((char*)"Bonus: around the block...", around_the_block )
	       .add ((char*)"Test a function",test);

	Menu sn_menu ((char*)"Velocity");
	sn_menu.add ((char*)"Quick", quick)
		   .add ((char*)"Normal",normal)
		   .add ((char*)"Slow",slow)
		   .add ((char*)"Very slow",very_slow);

	try
	{
		karelsWereld().Run (charles_menu,WINARGS(hInstance, hPrevInstance, szCmdLine, iCmdShow));
	}
	catch (IllegaleActie dezeIllegaleActie )
	{
		dezeIllegaleActie.report ();
	}
	catch (...)
	{
		makeAlert ("Something went terribly wrong!");
	}

	return 0;
}
