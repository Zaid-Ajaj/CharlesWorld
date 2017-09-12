#include "Robot.h"
/*
	Karel is a framework for manipulating with Karel the robot.
	Karel is a subclass of ROBOT from the library Robot.
	Last Modified:	September 16 2006, by Pieter Koopman, RU Nijmegen
	With some additions: September 12 2007, by Ger Paulussen & Peter Achten
	More additions: August 21 2013, by Peter Achten
*/


// =========================================================================

// make_church creates a Church-like shape of walls
void make_church ()
{
    const int lane   = 2 + rand () % (WereldHoogte / 5) ;
    const int street = 2 + rand () % (WereldBreedte / 5) ;
    const int width  = 3 + rand () % (WereldBreedte / 2) ;
    const int height = 2 + rand () % (WereldHoogte / 3) ;
    place_rectangle (street,lane,width,height) ;
    place_rectangle (street + 2,lane + height, 2 + width / 3, 2 + height / 3) ;
    place_walls (street + 3 + width / 6,lane + height + height / 3 + 3,4,false) ;
    place_walls (street + 2 + width / 6,lane + height + height / 3 + 5,2,true) ;
    create_ball (street, WereldHoogte - 2) ;
}

// safe_put_ball makes Charles put a ball on his current location if it is empty
void safe_put_ball ()
{
    if (!on_ball ())
        put_ball () ;
}

// safe_step makes Charles move one step ahead if not blocked by a wall
void safe_step ()
{
    if (!in_front_of_wall())
        step () ;
}

// balls (n) makes Charles place at most n balls straight ahead (if not blocked by a wall)
// in a safe way (putting balls only on empty spots)
void balls (int no_of_balls)
{
    for (int i = 1 ; i < no_of_balls ; i++)
    {
        safe_put_ball () ;
        safe_step () ;
    }
    if (no_of_balls > 0)
        safe_put_ball () ;
}

// here starts the part with code to be completed by the students

// Name / student number / study student 1 :
// Name / student number / study student 2 :

void turn_around()
{
	turn_left();
	turn_left();
}

void step_back()
{
	turn_around();
	step();
	turn_around();
}

boolean next_step_has_ball()
{
	if (in_front_of_wall())
	{
		// if there is a wall then there is no ball to pick up
		return false;
	}

	step();
	if (on_ball())
	{
		// ball found
		step_back();
		return true;
	}

	step_back();
	return false;
}

void find_next_path()
{
    turn_right();
    if (next_step_has_ball())
    {
        // next path found
        return;
    }

    turn_around();
    if (next_step_has_ball())
    {
        // next path found
        return;
    }

    turn_right();
}

// returns whether or not the path has ended by scanning the
// surroundings and checking that there is indeed no more balls left
boolean path_has_ended()
{
    if (next_step_has_ball())
    {
        return false;
    }

    turn_right();
    if (next_step_has_ball())
    {
        return false;
    }

    turn_around();
    if (next_step_has_ball())
    {
        return false;
    }

    turn_right();
    if (next_step_has_ball())
    {
        return false;
    }

    return true;
}

// Makes charles face east by first looking for the north side and
// then turning right
void turn_east()
{
    while(!north())
    {
        turn_right();
    }

    turn_right();
}
// give one or more comment lines about what will happen in this function
void follow_path ()
{
    while(!path_has_ended())
    {
        while(next_step_has_ball())
        {
            step();
        }

        find_next_path();
    }

    turn_east();
}

// give one or more comment lines about what will happen in this function
void hansl_and_gretl ()
{
	make_path_with_balls();
	follow_path () ;
}

void turn_west()
{
    turn_east();
    turn_around();
}



void put_balls_until_wall_reached()
{
    while(!in_front_of_wall())
    {
        put_ball();
        step();
    }

    // wall is in front, put last ball
    put_ball();
}

void put_balls_on_cave_line_and_come_back()
{
    put_balls_until_wall_reached();

    turn_around();
    while(!in_front_of_wall())
    {
        step();
    }
}
// give one or more comment lines about what will happen in this function
// note that you are allowed to add formal parameters to fill_cave_with_balls if that is necessary for your solution
void fill_cave_with_balls (boolean  fillingUpperHalf)
{
     step();
     while(!in_front_of_wall())
     {
         turn_left(); // face the wall
         turn_around();

         // the case where there is only one ball to fill between two walls
         if (in_front_of_wall())
         {
             put_ball();
             turn_left();
             step();
             continue;
         }

         put_balls_on_cave_line_and_come_back();
         turn_right();
         step();
     }

     if (fillingUpperHalf)
     {
        // after finishing the upper side,
        // prepare Charles for lower side
        turn_right();
        while(!in_front_of_wall())
        {
            step();
        }
        turn_right();
     }
     else
     {
         // Go back to initial position
         turn_right();
         while(!in_front_of_wall())
         {
             step();
         }

         turn_right();
     }
}

// give one or more comment lines about what will happen in this function
void cave ()
{
	// if necessary for your solution, you are allowed to give actual parameters to fill_cave_with_balls
	fill_cave_with_balls (true) ;
	fill_cave_with_balls (false) ;
}

// give one or more comment lines about what will happen in this function
void start_cave ()
{
    make_cave () ;
    cave () ;
}

// give one or more comment lines about what will happen in this function
void rondje_om_de_kerk ()
{
    make_church () ;
    // give your own code completion
}

// For testing purposes, you can define your own function here:
void test ()
{
    // enter your Charles code here
    balls (8/3) ;
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

	Menu a1_menu ((char*)"Assignment 2");
	a1_menu.add ((char*)"Hansl and Gretl", hansl_and_gretl )
		   .add ((char*)"Cave", start_cave )
		   .add ((char*)"Bonus: rondje om de kerk...", rondje_om_de_kerk )
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
