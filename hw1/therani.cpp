#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <math.h>

using namespace std;

int main(int argc, char* argv[])
{
    if(argc < 3) {
        cerr << "Please provide an input and output file." << endl;
        return 1;
    }
    ifstream input(argv[1]);
    ofstream output(argv[2]);

    if (input.fail())
    {
        output<<"Error - Input file doesn't exist!"<<endl;
        return 0;
    }

    int experiments;
    int check_START = -1;
    int *numsubjects;
    int total_subject;
    string **history;
    string line;
    string curr;


    while(getline(input, curr)) {
        bool Error_found = false;
        bool Check_empty = false;
        line = curr;
        stringstream ss;
        ss << curr;
        ss >> curr;
        if (curr == "START") {
            // Hint: This does not cover all errors yet.
            check_START++;
            if (ss.eof())
            {
                Check_empty = true;
            }
            double fractpart,totalpart,intpart;
            int n;
            ss >> totalpart;
            n = (int) totalpart;
            fractpart = modf(totalpart, &intpart);

            if (Check_empty) {

                output<<"Too few parameters:"<<line<<endl;
            }


            else if (fractpart != 0)
            {
                output << "Error - incorrect command: " << line << endl;
                output<<"Parameter should be an integer"<<endl;
            }


            else if (ss.fail()) {
                output << "Error - incorrect command: " << line << endl;
                output << "Parameter should be an integer" << endl;
            }
            else if (n < 0) {
                output << "Error - incorrect command: " << line << endl;
                output << "Number out of range" << endl;
            }
            else {
                experiments = 0;
                total_subject = n;

                numsubjects = new int[experiments+1]; // dynamic allocate
                numsubjects[0] = n;

                history = new string* [experiments+1]; //dynamic allocate the first row of history

                for (int i = 0; i < experiments+1; ++i)
                {
                    history[i] = new string[total_subject];
                }

                for(int j=0; j<experiments+1; j++) {    // assign value to history
                    for (int i = 0; i < n; ++i)
                    {
                        history[j][i]="";
                    }


                }
            }
        }

        else if (curr == "ADD") {

            if (check_START == -1)
            {
                output << "Error - no subjects yet " <<line << endl;
            }

            else {
                string **buffer_history  ; // create a new array to hold value
                int *buffer_numsubjects  ;
                experiments++;

                buffer_numsubjects = new int[experiments];

                buffer_history = new string* [experiments];
                for (int i = 0; i < experiments; ++i)
                {
                    buffer_history[i] = new string[total_subject];
                }

                for (int i = 0; i < experiments; ++i)
                {
                    buffer_numsubjects[i] = numsubjects[i]; // copy value in numsubjects

                    for (int j = 0; j < total_subject; ++j)
                    {
                        buffer_history[i][j] = history[i][j]; // copy value in history


                    }
                }

                for (int i = 0; i < experiments; ++i) // this section deallocate history and numsubject
                {
                    delete[] history[i];
                }

                delete[] history;
                delete[] numsubjects;


                numsubjects = new int[experiments+1]; // dynamic allocate new numsubjects
                numsubjects[experiments] = 0;



                history = new string* [experiments+1]; // dynamic allocate new history
                for (int i = 0; i < experiments+1; ++i)  // MISTAKE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                {
                    history[i] = new string[total_subject];
                }

                for (int i = 0; i < experiments; ++i)
                {
                    numsubjects[i] = buffer_numsubjects[i]; // copy value in numsubjects

                    for (int j = 0; j < total_subject; ++j)
                    {
                        history[i][j] = buffer_history[i][j]; // copy value in history

                    }
                }

                // assgin the new experiment and history to original value
                for (int i = 0; i < total_subject; ++i)
                {
                    history[experiments][i] = "";
                }

                for (int i = 0; i < experiments; ++i) // this section deallocate buffer array
                {
                    delete[] buffer_history[i];
                }

                delete[] buffer_history;
                delete[] buffer_numsubjects;
            }
        }

        else if (curr == "MOVE") {

            int start_experiment, end_experiment;
            int start_subject, end_subject;

            double db_x,db_y,db_n,db_m;
            double fract_x,fract_y,fract_n,fract_m;
            double intx,inty,intn,intm;

            ss>>db_x>>db_y;     // read input
            ss>>db_n;
                       
            if (ss.eof()) {
                Error_found = true;           
        }
       
            ss>>db_m;

            fract_x = modf(db_x,&intx);
            fract_y = modf(db_y,&inty);
            fract_n = modf(db_n,&intn);
            fract_m = modf(db_m,&intm);
          

            start_experiment = (int) db_x;
            end_experiment =(int) db_y ;
            start_subject =(int) db_n;
            end_subject =(int) db_m;


            if (check_START == -1)
            {
                output << "Error - no subjects yet "<<line  << endl;
            }

            else if (Error_found)
            {
                output<<"Too few parameters:"<<line<<endl;
            }
           
            else if (fract_x != 0 || fract_y != 0 || fract_m != 0 || fract_n != 0)
            {
                output << "Error - incorrect command: " << line << endl;
                output<<"Parameter should be an integer"<<endl;
            }



            else if (start_experiment < 0 || end_experiment<0 || start_subject<0 || end_subject<0) {
                output << "Error - incorrect command: " << line << endl;
                output << "Number out of range" << endl;
            }

            else if ((start_experiment || end_experiment) > experiments || end_subject > numsubjects[start_experiment])
            {
                output << "Error - incorrect command: " << line << endl;
                output << "Number out of range" << endl;
            }

            else if (start_subject > end_subject)
            {
                output << "Error - incorrect command: " << line << endl;
                output << "Invalid range of subjects to move" << endl;
            }

            else {
                for (int i = 0; i < end_subject- start_subject+1 ; ++i) // update history
                {

                    string add_history =  to_string(end_experiment) + " ";
                    history[start_experiment][start_subject+i] += add_history; // update the string inside history

                    history[end_experiment][numsubjects[end_experiment]] = history[start_experiment][start_subject+i]; // update destination experiment first
                    numsubjects[end_experiment]++; // add to numsubject

                    history[start_experiment][start_subject+i] = " ";

                    if (numsubjects[start_experiment] -1 - end_subject > i) // MISTAKE!!!!!!!!!!!!!!!!!!
                    {
                        history[start_experiment][start_subject+i] = history[start_experiment][end_subject+i+1];  // update the start experiment, move the back subjects forward.

                        history[start_experiment][end_subject+i+1] = " ";
                    }
                    numsubjects[start_experiment] --; // one subject has been moved to another experiment!
                }

            }
        }

        else if (curr == "QUERY") {

            double doublex,doubley,intx,inty,fractx,fracty;
            int experiment_x, nth_subject;

            ss >> doublex;

            if (ss.eof()) {
                Error_found = true;
            }
            ss >> doubley;
            fractx = modf(doublex,&intx);
            fracty = modf(doubley, &inty);

            experiment_x =(int) doublex;
            nth_subject = (int) doubley;

            if (check_START == -1)
            {
                output << "Error - no subjects yet "<<line  << endl;
            }

            else if (Error_found) {
                output<<"Too few parameters:"<<line<<endl;
            }

            else if (fractx != 0 || fracty != 0)
            {
                output << "Error - incorrect command: " << line << endl;
                output<<"Parameter should be an integer"<<endl;
            }

            else if (experiment_x < 0 || nth_subject < 0) {
                output << "Error - incorrect command: " << line << endl;
                output << "Number out of range" << endl;
            }
            else if (experiment_x > experiments || nth_subject > numsubjects[experiments])
            {
                output << "Error - incorrect command: " << line << endl;
                output << "Number out of range" << endl;
            }



            else output<<history[experiment_x][nth_subject]<<endl; // output Query to argv[2]

        }

        else {
            output<<"Command does not exist:"<<line<<endl;
        }

    }

   if (check_START != -1)
   {
  	
    for (int i = 0; i < experiments+1; ++i) // this section deallocate history and numsubject
    {
        delete[] history[i];
    }

    delete[] history;
    delete[] numsubjects;
}

    input.close();
    output.close();

    return 0;
}
