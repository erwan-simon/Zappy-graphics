#ifndef CHARACTER_H_
# define CHARACTER_H_

# include <memory>

class Map;

class 			Character {
    public:
	Character(int id, Map &map);
	Character(std::string &args, Map &map);
	~Character();

	int 		GetId() const;
	const int*	GetLocation() const;
	void		Setlocation(int x, int y);
	bool		ConsumeFood();
	void 		AddFood(int foodNb);
	Character &	operator=(Character const &other);

    private:
	int 		id;
	Map 		&map;
	int 		location[2] = {0, 0}; // {x, y}
	int 		food = 5;
};

#endif /* CHARACTER_H_ */
