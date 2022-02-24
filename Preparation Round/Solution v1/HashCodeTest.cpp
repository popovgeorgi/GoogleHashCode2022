#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <map>

struct Ingredient {
    int id;
    std::string str;
    int strl;
};

struct Person {
    std::vector<Ingredient> like;
    std::vector<Ingredient> dislike;
};



bool hasElement(std::vector<Ingredient> ing, Ingredient ind) {
    for (size_t i = 0; i < ing.size(); i++)
    {
        if (ind.id == ing[i].id) {
            return true;
        }
    }
    return false;
}

void addIng(std::vector<Ingredient>& ing, Ingredient ind) {
    if (!hasElement(ing, ind)) {
        ing.push_back(ind);
    }
}



int hasElement(std::vector<Ingredient> ing, std::string ind) {
    int indl = ind.length();
    for (size_t i = 0; i < ing.size(); i++)
    {
        if (indl != ing[i].strl) {
            continue;
        }
        int j = indl - 1;
        bool t = true;
        while (j >= 0) {
            if (ind[j] != ing[i].str[j]) {
                t = false;
                break;
            }
            --j;
        }

        if (t) {
            return i;
        }
    }
    return -1;
}


void input(std::vector<Person>& people, std::vector<Ingredient>& ing) {
    std::ifstream inp;

    inp.open("input-3.txt");
     
    int n;
    inp >> n;

    int l;

    for (size_t i = 0; i < n; i++)
    {
        Person current;

        inp >> l;
        for (size_t j = 0; j < l; j++)
        {
            std::string a;
            inp >> a;
            int b = hasElement(ing, a);
            if (b==-1) {
                b = ing.size() + 1;
                ing.push_back(Ingredient{b,a, (int)a.length()});
                b = ing.size()-1;
            }
            current.like.push_back(ing[b]);
        }

        inp >> l;
        for (size_t j = 0; j < l; j++)
        {
            std::string a;
            inp >> a;
            int b = hasElement(ing, a);
            if (b == -1) {
                b = ing.size() + 1;
                ing.push_back(Ingredient{ b,a, (int)a.length() });
                b = ing.size() - 1;
            }
            current.dislike.push_back(ing[b]);
        }

        people.push_back(current);
    }
}

int countLikes(std::vector<Person> people, Ingredient str, Ingredient str2) {
    int count = 0;
    for (size_t i = 0; i < people.size(); i++)
    {
        if (hasElement(people[i].like, str) && hasElement(people[i].like, str2)) {
            ++count;
        }
    }

    return count;
}

int countDislikes(std::vector<Person> people, Ingredient str) {
    int count = 0;
    for (size_t i = 0; i < people.size(); i++)
    {
        if (hasElement(people[i].dislike, str)) {
            ++count;
        }
    }

    return count;
}


int main()
{
    std::vector<Person> people;
    std::vector<Ingredient> ing;
    std::map<int, int> likes;
    std::map<int, int> dislikes;

    std::vector<Ingredient> pot;

    input(people,ing);
    std::cout << "Input ready - "<<people.size() << " "<< ing.size() << std::endl;
    for (size_t i = 0; i < ing.size(); i++)
    {

        int likecount = 0;
        int dislikecount = 0;

        for (size_t j = 0; j < people.size(); j++)
        {
            if (hasElement(people[j].like, ing[i])) {
                ++likecount;
            }
            if (hasElement(people[j].dislike, ing[i])) {
                ++dislikecount;
            }
        }

        likes[ing[i].id] = likecount;
        dislikes[ing[i].id] = dislikecount;
    }
    std::cout << "Like / Dislike ready" << std::endl;

    for (size_t i = 0; i < ing.size(); i++)
    {
        std::cout << i << std::endl;
        if (likes[ing[i].id] > dislikes[ing[i].id]) {
            pot.push_back(ing[i]);
        }
        else {
            for (size_t m = 0; m < pot.size(); m++)
            {
                likes[pot[m].id] = likes[pot[m].id] - countLikes(people, ing[i], pot[m]);

                if (likes[pot[m].id] < dislikes[pot[m].id]) {
                    pot.erase(pot.begin()+m);
                    --m;
                }
            }
        }
    }

    std::cout << pot.size()<<" ";

    for (size_t i = 0; i < pot.size(); i++)
    {
        std::cout << pot[i].str << " ";
    }
}
