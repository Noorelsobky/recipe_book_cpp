#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int num_users = 10;
const int num_admins = 5;
const int num_recipes = 10;
const int num_fav = 10;

struct USER {
    string user_username;
    string user_pass;

};
struct ADMIN {
    string admin_username;
    string admin_pass;
};
struct RECIPE {
    string R_id;
    string R_name;
    string R_ingredients;
    string R_instructions;
    string R_time;
    string R_level;
};
RECIPE fav[num_fav];

//user login info arry
USER users[num_users] = {
    {"Dr.Esraa","Dr.Esraa_pass"},
    {"user","user"}
};

//admin login info arry
ADMIN admins[num_admins] = {
    {"sohaila","sohaila_pass"},
    {"sondos","sondos_pass"},
    {"noor","noor_pass"},
    {"malak ","malak_pass"},
    {"yougine","yougine_pass"}
};

//recipes arry
RECIPE recipe[num_recipes] = {
    {"001", "spaghetti bolognese", "spaghetti, minced beef, tomato sauce, onion, garlic", "boil spaghetti, cook beef with sauce and veggies", "30 mins", "easy"},
    {"002", "chicken curry", "chicken, curry paste, coconut milk, onion, garlic, ginger", "cook chicken with curry paste, add coconut milk", "45 mins", "medium"},
    {"003", "grilled cheese", "bread, cheese, butter", "butter bread, place cheese inside, grill until golden", "10 mins", "easy"},
    {"004", "pancakes", "flour, milk, egg, sugar, butter", "mix ingredients, pour on pan, flip when bubbly", "20 mins", "easy"},
    {"005", "beef stroganoff", "beef, mushrooms, sour cream, onion, butter", "cook beef and mushrooms, add cream and simmer", "40 mins", "hard"}
};

//decleraions
int start_menu();
int login();
bool sign_up(int& count_users);
int admin_menu();
int user_menu();
void add(int&);
void logout(int used_recipes, int count_users, int favcount);
void display_recipe(int& used_recipes);
void display_fav(int& favcount);
void random_R(RECIPE recipe[], int& used_recipes);
void admin_switch(int& used_recipes, int count_users, int favcount);
void user_switch(int& favcount, int& used_recipes, int count_users);
void del_recipe(RECIPE recipe[], int& used_recipes);
void del_fav(RECIPE fav[], int& favcount);
void add_favourite(RECIPE recipe[], RECIPE fav[num_fav], int& favcount, int& used_recipes);
void search(RECIPE recipe[], int& used_recipes);
void search_ingredients(RECIPE recipe[], int& used_recipes);
void search_name(RECIPE recipe[], int& used_recipes);
void search_level(RECIPE recipe[], int& used_recipes);
void edit(int& used_recipes);
void loadRecipesFromFile(RECIPE recipe[], int& used_recipes);
void saveRecipesToFile(RECIPE recipe[], int used_recipes);
void loadUsersFromFile(USER users[], int& count_users);
void saveUsersToFile(USER users[], int count_users);
void loadFavoritesFromFile(RECIPE fav[], int& favcount);
void saveFavoritesToFile(RECIPE fav[], int favcount);


//MAIN
int main() {

    int used_recipes = 5;
    int favcount = 0;
    int count_users = 5;//to know where to add the new user
    int s_choice;
    loadRecipesFromFile(recipe, used_recipes);
    loadUsersFromFile(users, count_users);
    loadFavoritesFromFile(fav, favcount);

    do {
        s_choice = start_menu();

        switch (s_choice) {
        case 1: {
            int x = login();
            switch (x) {
            case 1:
                admin_switch(used_recipes, count_users, favcount);
                break;

            case 2: user_switch(favcount, used_recipes, count_users);
                break;

            }
        }
              break;
        case 2:
        {
            if (sign_up(count_users) == true)
                user_switch(favcount, used_recipes, count_users);


        }
        break;

        case 3:exit(0);
            break;
        default:cout << "<<< Invalid Option! >>>" << endl;
            cout << endl;



        }

    } while (s_choice != 3);


}


//Definitions

void loadRecipesFromFile(RECIPE recipe[], int& used_recipes) {
    
    //to read from file

    ifstream inFile("recipes.txt");

    if (!inFile) {
        cout << "Error opening file for reading!" << endl;
        return;
    }

    used_recipes = 0;
    while (used_recipes < num_recipes && getline(inFile, recipe[used_recipes].R_id)) {
        getline(inFile, recipe[used_recipes].R_name);
        getline(inFile, recipe[used_recipes].R_ingredients);
        getline(inFile, recipe[used_recipes].R_instructions);
        getline(inFile, recipe[used_recipes].R_time);
        getline(inFile, recipe[used_recipes].R_level);
        string separator;
        getline(inFile, separator);
        used_recipes++;
    }

    inFile.close();
    cout << "Recipes loaded successfully." << endl;
}

void saveRecipesToFile(RECIPE recipe[], int used_recipes) {

    //write into file

    ofstream outFile("recipes.txt");

    if (!outFile) {
        cout << "Error opening file for writing!" << endl;
        return;
    }

    for (int i = 0; i < used_recipes; i++) {
        outFile << recipe[i].R_id << endl;
        outFile << recipe[i].R_name << endl;
        outFile << recipe[i].R_ingredients << endl;
        outFile << recipe[i].R_instructions << endl;
        outFile << recipe[i].R_time << endl;
        outFile << recipe[i].R_level << endl;
        outFile << "---" << endl;
    }

    outFile.close();
    cout << "Recipes saved successfully." << endl;
}

void loadUsersFromFile(USER users[], int& count_users) {

    //to read from file

    ifstream inFile("users.txt");

    if (!inFile) {
        cout << "Error opening file for reading users!" << endl;
        return;
    }

    count_users = 0;
    while (count_users < num_users && getline(inFile, users[count_users].user_username)) {
        getline(inFile, users[count_users].user_pass);
        count_users++;
    }

    inFile.close();
    cout << "Users loaded successfully." << endl;
}

void saveUsersToFile(USER users[], int count_users) {

    //write into file

    ofstream outFile("users.txt");

    if (!outFile) {
        cout << "Error opening file for writing users!" << endl;
        return;
    }

    for (int i = 0; i < count_users; i++) {
        outFile << users[i].user_username << endl;
        outFile << users[i].user_pass << endl;
    }

    outFile.close();
    cout << "Users saved successfully." << endl;
}

void loadFavoritesFromFile(RECIPE fav[], int& favcount) {

    //to read from file

    ifstream inFile("favorites.txt");

    if (!inFile) {
        cout << "Error opening file for reading favorites!" << endl;
        return;
    }

    favcount = 0;
    while (favcount < num_fav && getline(inFile, fav[favcount].R_id)) {
        getline(inFile, fav[favcount].R_name);
        getline(inFile, fav[favcount].R_ingredients);
        getline(inFile, fav[favcount].R_instructions);
        getline(inFile, fav[favcount].R_time);
        getline(inFile, fav[favcount].R_level);
        string separator;
        getline(inFile, separator);
        favcount++;
    }

    inFile.close();
    cout << "Favorites loaded successfully." << endl;
}

void saveFavoritesToFile(RECIPE fav[], int favcount) {

    //write into file

    ofstream outFile("favorites.txt");

    if (!outFile) {
        cout << "Error opening file for writing favorites!" << endl;
        return;
    }

    for (int i = 0; i < favcount; i++) {
        outFile << fav[i].R_id << endl;
        outFile << fav[i].R_name << endl;
        outFile << fav[i].R_ingredients << endl;
        outFile << fav[i].R_instructions << endl;
        outFile << fav[i].R_time << endl;
        outFile << fav[i].R_level << endl;
        outFile << "---" << endl;
    }

    outFile.close();
    cout << "Favorites saved successfully." << endl;
}




int start_menu() {
    int s_choice;
    cout << "========= WELCOME TO RECIPE BOOK!! =========" << endl;
    cout << endl;
    cout << "1-Login" << endl;
    cout << "2-Sign_up" << endl;
    cout << "3-Exit" << endl;
    cin >> s_choice;
    cout << endl;
    return s_choice;
}


int login() {
    string u, p;//user,pasword entered


    cout << "Enter username: ";
    cin.ignore();
    getline(cin, u);
    while (u == "") {
        cout << "<<<Please fill the field before continuing! >>>" << endl;
        cout << "Enter username: ";
        getline(cin, u);
    }

    cout << "Enter password: ";
    getline(cin, p);
    while (p == "") {
        cout << "<<<Please fill the field before continuing! >>>" << endl;
        cout << "Enter password: ";
        getline(cin, p);
    }

    //loop to check the user&pass entered with the users_array
    for (int i = 0;i < num_users;i++) {
        if (users[i].user_username == u && users[i].user_pass == p) {
            cout << "<<< Hello " << u << "! >>>" << endl;
            //user_menu();
            return 2;
        }

    }
    //loop to check the user&pass entered with the admins_array
    for (int i = 0;i < num_admins;i++) {
        if (admins[i].admin_username == u && admins[i].admin_pass == p) {
            cout << "<<< Hello " << u << "! >>>" << endl;
            //admin_menu();
            return 1;
        }
    }

    cout << "<<< Invalid username or password.Try again. >>>" << endl;
    cout << endl;

    return 0;
}


bool sign_up(int& count_users) {


    string new_u, new_p;
    cout << "Enter username:";
    cin.ignore();
    getline(cin, new_u);
    while (new_u == "")
    {
        cout << "<<<Please fill the field before continuing! >>>" << endl;
        cout << "Enter username: ";
        getline(cin, new_u);
    }



    if (count_users >= num_users) {
        cout << "<<< User limit reached. Cannot register more users. >>>" << endl;
        return false;
    }


    for (int i = 0; i < count_users; i++) {
        if (users[i].user_username == new_u)
        {
            cout << endl;
            cout << "<<< Username already exists. Try again. >>>" << endl;
            return false;

        }
    }

    for (int i = 0; i < num_admins; i++) {
        if (admins[i].admin_username == new_u) {
            cout << endl;
            cout << "<<< Username already exists. Try again. >>>" << endl;
            return false;
        }

    }
    cout << "Enter password:";
    getline(cin, new_p);
    while (new_p == "")
    {
        cout << "<<<Please fill the field before continuing! >>>" << endl;
        cout << "Enter password: ";
        getline(cin, new_p);
    }
    cout << endl;
    cout << "<<< Hello " << new_u << "! you have successfully registered. >>>" << endl;
    cout << endl;
    users[count_users].user_username = new_u;
    users[count_users].user_pass = new_p;
    count_users++;
    return true;

}


void logout(int used_recipes, int count_users, int favcount) {
    cout << "<<< You have successfully logged out. >>>" << endl;
    cout << endl;
    //write inti the file (outfile)
    saveRecipesToFile(recipe, used_recipes);
    saveUsersToFile(users, count_users);
    saveFavoritesToFile(fav, favcount);

    cout << "\nData saved. Logging out..." << endl;
}



int admin_menu() {
    int a_choice;
    cout << "\n================== MENU ================= \n";
    cout << "\n";
    cout << "1. Add new recipe" << endl;
    cout << "2. Edit recipe" << endl;
    cout << "3. Delete recipe" << endl;
    cout << "4. View all recipes" << endl;
    cout << "5. Logout" << endl;
    cin >> a_choice;

    return a_choice;

}

void admin_switch(int& used_recipes, int count_users, int favcount) {

    int a_choice;
    do {
        a_choice = admin_menu();

        switch (a_choice) {
        case 1:add(used_recipes);
            break;
        case 2:edit(used_recipes);
            break;
        case 3:del_recipe(recipe, used_recipes);
            break;
        case 4:display_recipe(used_recipes);
            break;
        case 5:logout(used_recipes, count_users, favcount);
            return;
        default:cout << "<<< Invalid Option! >>>" << endl;

        }


    } while (true);

}



int user_menu() {
    int u_choice;
    cout << "\n================== MENU ================= \n";
    cout << "\n";
    cout << "Choose an option from the following :" << endl;
    cout << "1. Display recipes " << endl;
    cout << "2. Search recipe " << endl;
    cout << "3. Add Favorite recipe" << endl;
    cout << "4. Delete Favorite recipe from list " << endl;
    cout << "5. Display favorite recipes " << endl;
    cout << "6. Recipe generator  " << endl;
    cout << "7. Logout " << endl;
    cin >> u_choice;
    return u_choice;

}

void user_switch(int& favcount, int& used_recipes, int count_users) {

    int u_choice;

    do {
        u_choice = user_menu();

        switch (u_choice) {
        case 1:display_recipe(used_recipes);
            break;
        case 2:search(recipe, used_recipes);
            break;
        case 3:
            add_favourite(recipe, fav, favcount, used_recipes);
            break;
        case 4:
            del_fav(fav, favcount);
            break;
        case 5:
            display_fav(favcount);
            break;
        case 6:random_R(recipe, used_recipes);
            break;
        case 7:logout(used_recipes, count_users, favcount);
            return;
        default:cout << "<<< Invalid Option! >>>" << endl;
        }

    } while (true);

}

void display_recipe(int& used_recipes) {
    for (int i = 0;i < used_recipes;i++) {
        cout << "--------------------------------------------" << endl;
        cout << recipe[i].R_id << "- " << recipe[i].R_name << endl;
        cout << endl;
        cout << " ~> Ingredients: " << recipe[i].R_ingredients << endl;
        cout << endl;
        cout << " ~> Instructions: " << recipe[i].R_instructions << endl;
        cout << endl;
        cout << " ~> Cooking-Time: " << recipe[i].R_time << endl;
        cout << endl;
        cout << " ~> Difficulty-Level: " << recipe[i].R_level << endl;
        cout << "--------------------------------------------";
        cout << endl;
    }
}

void random_R(RECIPE recipe[], int& used_recipes)
{
    int random_index;

    random_index = rand() % used_recipes;

    cout << "--------------------------------------------" << endl;
    cout << recipe[random_index].R_id << "- " << recipe[random_index].R_name << endl;
    cout << endl;
    cout << " ~> Ingredients: " << recipe[random_index].R_ingredients << endl;
    cout << endl;
    cout << " ~> Instructions: " << recipe[random_index].R_instructions << endl;
    cout << endl;
    cout << " ~> Cooking-Time: " << recipe[random_index].R_time << endl;
    cout << endl;
    cout << " ~> Difficulty-Level: " << recipe[random_index].R_level << endl;
    cout << "--------------------------------------------";
    cout << endl;


}


void add(int& used_recipes)
{
    cout << "Enter Recipe ID: " << endl;
    cin >> recipe[used_recipes].R_id;

    for (int i = 0;i < used_recipes;i++) {
        while (recipe[used_recipes].R_id == recipe[i].R_id) {
            cout << "<<< ID already taken! Please enter another ID. >>>" << endl;
            cin >> recipe[used_recipes].R_id;
        }
    }

    cout << "Enter your new Recipe Name: ";
    cin.ignore();
    getline(cin, recipe[used_recipes].R_name);
    while (recipe[used_recipes].R_name == "") {
        cout << "<<<Please fill the field before continuing! >>>" << endl;
        cout << "Enter your new Recipe Name: ";
        getline(cin, recipe[used_recipes].R_name);
    }

    cout << "Enter the Ingredients: ";
    getline(cin, recipe[used_recipes].R_ingredients);
    while (recipe[used_recipes].R_ingredients == "") {
        cout << "<<<Please fill the field before continuing! >>>" << endl;
        cout << "Enter the Ingredients: ";
        getline(cin, recipe[used_recipes].R_ingredients);
    }

    cout << "Enter the Instructions: ";
    getline(cin, recipe[used_recipes].R_instructions);
    while (recipe[used_recipes].R_instructions == "") {
        cout << "<<<Please fill the field before continuing! >>>" << endl;
        cout << "Enter the Instructions: ";
        getline(cin, recipe[used_recipes].R_instructions);
    }

    cout << "Enter Cooking-Time: ";
    getline(cin, recipe[used_recipes].R_time);
    while (recipe[used_recipes].R_time == "") {
        cout << "<<<Please fill the field before continuing! >>>" << endl;
        cout << "Enter Cooking-Time: ";
        getline(cin, recipe[used_recipes].R_time);
    }

    cout << "Enter Difficulty-Level: ";
    cin >> recipe[used_recipes].R_level;
    while (recipe[used_recipes].R_time == "") {
        cout << "<<<Please fill the field before continuing! >>>" << endl;
        cout << "Enter Difficulty-Level: ";
        cin >> recipe[used_recipes].R_level;
    }

    used_recipes++;

}




void add_favourite(RECIPE recipe[], RECIPE fav[num_fav], int& favcount, int& used_recipes)
{
    string answer;

    if (favcount >= num_fav) {
        cout << "<<< Favorite list is full. >>>" << endl;
        return;
    }

    display_recipe(used_recipes);

    do {
        string id;
        bool found_fav = false;
        bool found_rec = false;


        cout << "Enter the Recipe id you want to add to favourites: ";
        cin >> id;


        for (int j = 0; j < favcount; j++) {
            if (fav[j].R_id == id) {
                cout << "<<< Recipe is already in favorites. >>>" << endl;
                found_fav = true;
                break;
            }
        }
        if (found_fav)
            continue;

        for (int i = 0;i < used_recipes;i++)
        {
            if (id == recipe[i].R_id)
            {
                fav[favcount] = recipe[i];
                found_rec = true;
                favcount++;
                break;
            }

        }
        if (found_rec) {
            cout << "<<< Recipe added to favourites successfully. >>>" << endl;
            cout << endl;
        }

        else {
            cout << "<<< Recipe ID is invalid! >>>" << endl << endl;
            continue;
        }

        cout << "Do you want to add another recipe? ";
        cin >> answer;
        cout << endl;

        while (answer != "yes" && answer != "Yes" && answer != "no" && answer != "No") {
            cout << "<<< Invalid input. Please enter 'yes' or 'no'. >>>" << endl;
            cout << "Do you want to add another recipe (yes/no)? ";
            cin >> answer;
            cout << endl;
        }

    } while (answer == "yes" || answer == "Yes");
}



void del_recipe(RECIPE recipe[], int& used_recipes)
{
    string answer;
    do {

        if (used_recipes == 0) {
            cout << "--------------- No Recipes avalible to delete ----------------";
            cout << endl;
            return;
        }
        int rec = -1;
        string id;

        cout << "Enter the id of recipe you want to delete: ";
        cin >> id;
        cout << endl;

        for (int i = 0; i < used_recipes; i++) {
            if (id == recipe[i].R_id) {
                rec = i;
                break;
            }
        }

        if (rec == -1) {
            cout << "<<< Recipe ID not found. >>>" << endl;
            continue;
        }

        for (int i = rec; i < used_recipes ; i++) {
            recipe[i] = recipe[i + 1];
        }

        used_recipes--;
        cout << "<<< Recipe deleted successfully. >>>" << endl;
        cout << endl;

        cout << "Do you want to delete another recipe ?" << endl;
        cin >> answer;


        while (answer != "yes" && answer != "Yes" && answer != "no" && answer != "No") {
            cout << "<<< Invalid input. Please enter 'yes' or 'no'. >>>" << endl;
            cout << "Do you want to delete another recipe (yes/no)? ";
            cin >> answer;
        }
    } while (answer != "no" && answer != "No");

}




void del_fav(RECIPE fav[], int& favcount)
{
    string answer;
    do {
        if (favcount == 0) {
            cout << "--------------- No Favourtie Recipes avalible to delete -----------------";
            cout << endl;
            return;

        }

        int rec = -1;
        string id;

        cout << "Enter the id of recipe you want to delete: ";
        cin >> id;
        cout << endl;

        for (int i = 0; i < favcount; i++) {
            if (id == fav[i].R_id) {
                rec = i;
                break;
            }
        }


        if (rec == -1) {
            cout << "Recipe ID not found." << endl;
            continue;
        }



        for (int i = rec; i < favcount ; i++) {
            fav[i] = fav[i + 1];
        }



        favcount--;
        cout << "Recipe deleted from favourites successfully." << endl;
        cout << endl;

        cout << "Do you want to delete another recipe ?" << endl;
        cout << endl;
        cin >> answer;
        while (answer != "yes" && answer != "Yes" && answer != "no" && answer != "No") {
            cout << "<<< Invalid input. Please enter 'yes' or 'no'. >>>" << endl;
            cout << "Do you want to delete another recipe (yes/no)? ";
            cin >> answer;
        }
    } while (answer != "no" && answer != "No");

}


void display_fav(int& favcount) {

    cout << "------------- Favoritre Recipes ------------" << endl;
    for (int i = 0;i < favcount;i++) {
        cout << "--------------------------------------------" << endl;
        cout << fav[i].R_id << "- " << fav[i].R_name << endl;
        cout << endl;
        cout << " ~> Ingredients: " << fav[i].R_ingredients << endl;
        cout << endl;
        cout << " ~> Instructions: " << fav[i].R_instructions << endl;
        cout << endl;
        cout << " ~> Cooking-Time: " << fav[i].R_time << endl;
        cout << endl;
        cout << " ~> Difficulty-Level: " << fav[i].R_level << endl;
        cout << "--------------------------------------------";
        cout << endl;
    }
}

void search(RECIPE recipe[], int& used_recipes) {
    int search;

    cout << "Choose the number for your type of search:" << endl;
    cout << "1. Search by Name" << endl;
    cout << "2. Search by Ingredients" << endl;
    cout << "3. Search by Difficulty-level" << endl;
    cin >> search;

    switch (search)
    {
    case 1:
        search_name(recipe, used_recipes);
        break;
    case 2:
        search_ingredients(recipe, used_recipes);
        break;
    case 3:
        search_level(recipe, used_recipes);
        break;
    default:cout << "<<< Invalid choice. Try Again. >>>";
        break;
    }


}

void search_name(RECIPE recipe[], int& used_recipes)
{
    string name;
    cout << "Enter your Recipe-Name: ";
    cin.ignore();
    getline(cin, name);
    while (name == "")
    {
        cout << "<<<Please fill the field before continuing! >>>" << endl;
        cout << "Enter your Recipe-Name: ";
        getline(cin, name);
    }
    bool found = false;

    for (int i = 0;i < used_recipes;i++)
    {
        if (name == recipe[i].R_name)
        {
            cout << "--------------------------------------------" << endl;
            cout << recipe[i].R_id << "- " << recipe[i].R_name << endl;
            cout << endl;
            cout << " ~> Ingredients: " << recipe[i].R_ingredients << endl;
            cout << endl;
            cout << " ~> Instructions: " << recipe[i].R_instructions << endl;
            cout << endl;
            cout << " ~> Cooking-Time: " << recipe[i].R_time << endl;
            cout << endl;
            cout << " ~> Difficulty-Level: " << recipe[i].R_level << endl;
            cout << "--------------------------------------------";
            cout << endl;
            found = true;
        }

    }
    if (!found) {
        cout << endl;
        cout << "<<< Recipe Name not found! >>>" << endl;
    }

}


void search_level(RECIPE recipe[], int& used_recipes)
{
    string level;
    bool found = false;

    cout << "Choose Level of Difficulty to search by: ";
    cin.ignore();
    getline(cin, level);
    while (level == "")
    {
        cout << "<<<Please fill the field before continuing! >>>" << endl;
        cout << "Choose Level of Difficulty to search by: ";
        getline(cin, level);
    }

    for (int i = 0;i < used_recipes;i++)
    {
        if (level == recipe[i].R_level)
        {

            cout << "--------------------------------------------" << endl;
            cout << recipe[i].R_id << "- " << recipe[i].R_name << endl;
            cout << endl;
            cout << " ~> Ingredients: " << recipe[i].R_ingredients << endl;
            cout << endl;
            cout << " ~> Instructions: " << recipe[i].R_instructions << endl;
            cout << endl;
            cout << " ~> Cooking-Time: " << recipe[i].R_time << endl;
            cout << endl;
            cout << " ~> Difficulty-Level: " << recipe[i].R_level << endl;
            cout << "--------------------------------------------";
            cout << endl;
            found = true;
        }


    }
    if (!found) {
        cout << "<<< Recipe Level not found! >>>" << endl;
    }
}

void search_ingredients(RECIPE recipe[], int& used_recipes) {

    string ingredient;
    int choice;
    cout << "Do you want to search for:" << endl;
    cout << "1- Recipes that INCLUDE this ingredient" << endl;
    cout << "2- Recipes that DO NOT INCLUDE this ingredient" << endl;
    cin >> choice;
    cin.ignore();

    while (choice != 1 && choice != 2) {
        cout << "<<< Invalid option. Try again. >>>>" << endl;
        cout << "Do you want to search for:" << endl;
        cout << "1- Recipes that INCLUDE this ingredient" << endl;
        cout << "2- Recipes that DO NOT INCLUDE this ingredient" << endl;
        cin >> choice;
        cin.ignore();

    }

    cout << "Enter the ingredient you want to search for:";
    getline(cin, ingredient);

    while (ingredient == "")
    {
        cout << "<<<Please fill the field before continuing! >>>" << endl;
        cout << "Enter the ingredient you want to search for: " << endl;
        getline(cin, ingredient);
    }

    bool found = false;

    for (int i = 0; i < used_recipes; i++) {
        bool include = recipe[i].R_ingredients.find(ingredient) != string::npos;

        if ((choice == 1 && include) || (choice == 2 && !include)) {
            cout << "--------------------------------------------" << endl;
            cout << recipe[i].R_id << "- " << recipe[i].R_name << endl;
            cout << endl;
            cout << " ~> Ingredients: " << recipe[i].R_ingredients << endl;
            cout << endl;
            cout << " ~> Instructions: " << recipe[i].R_instructions << endl;
            cout << endl;
            cout << " ~> Cooking-Time: " << recipe[i].R_time << endl;
            cout << endl;
            cout << " ~> Difficulty-Level: " << recipe[i].R_level << endl;
            cout << "--------------------------------------------";
            cout << endl;
            found = true;
        }



    }

    if (!found) {
        cout << "<<< No recipes found matching your conditions! >>>" << endl;
    }
}




void edit(int& used_recipes) {
    int edit_choice;
    string id;
    int field_choice;

    cout << "Enter the ID of the recipe you want to edit: ";
    cin >> id;

    for (int i = 0; i < used_recipes; i++) {
        if (id == recipe[i].R_id) {
            cout << "\nEditing Recipe: " << endl;
            cout << recipe[i].R_id << "- " << recipe[i].R_name << endl;
            cout << endl;
            cout << " 1 ~> Ingredients: " << recipe[i].R_ingredients << endl;
            cout << endl;
            cout << " 2 ~> Instructions: " << recipe[i].R_instructions << endl;
            cout << endl;
            cout << " 3  ~> Cooking-Time: " << recipe[i].R_time << endl;
            cout << endl;
            cout << " 4  ~> Difficulty-Level: " << recipe[i].R_level << endl;
            cout << "--------------------------------------------";
            cout << endl;

            cout << "What field do you want to edit (1-4)? ";
            cin >> field_choice;
            cin.ignore();

            string* field_ptr = nullptr;

            switch (field_choice) {//to locate the address
            case 1: field_ptr = &recipe[i].R_ingredients;
                break;
            case 2: field_ptr = &recipe[i].R_instructions;
                break;
            case 3: field_ptr = &recipe[i].R_time;
                break;
            case 4: field_ptr = &recipe[i].R_level;
                break;
            default: cout << "<<< Invalid field choice. >>>" << endl;
                return;
            }

            cout << "How do you want to edit the selected field?" << endl;
            cout << "1. Remove" << endl;
            cout << "2. Add" << endl;
            cout << "3. Replace" << endl;

            cin >> edit_choice;
            cin.ignore();

            string& text = *field_ptr;
            string targetText, newText;

            switch (edit_choice) {
            case 1:
                cout << "Enter the text to remove: ";
                getline(cin, newText);
                if (!newText.empty()) {
                    size_t pos = text.find(newText);
                    if (pos != string::npos) {
                        text.erase(pos, newText.length());
                        cout << "<<< Removed successfully. >>>" << endl;
                    }
                    else {
                        cout << "<<< Text not found in the field! >>>" << endl;
                    }
                }
                break;

            case 2:
                cout << "Enter the text to add: ";
                getline(cin, newText);
                if (!newText.empty()) {
                    if (!text.empty())
                        text += ", ";
                    text += newText;
                    cout << "<<< Added successfully. >>>" << endl;
                }
                break;

            case 3:
                cout << "Enter the text to replace: ";
                getline(cin, targetText);
                cout << "Enter the new text: ";
                getline(cin, newText);
                if (!targetText.empty() && !newText.empty()) {
                    size_t pos = text.find(targetText);
                    if (pos != string::npos) {
                        text.replace(pos, targetText.length(), newText);
                        cout << "<<< Replaced successfully. >>>" << endl;
                    }
                    else {
                        cout << "<<< Text to replace not found! >>>" << endl;
                    }
                }
                break;

            default:
                cout << "<<< Invalid edit choice! >>" << endl;
                break;
            }

            return;
        }
    }

    cout << "<<< Recipe with ID '" << id << "' not found! >>>" << endl;
}
