#ifndef MAP_H_
# define MAP_H_

# include <vector>
# include <memory>
# include "Box.h"
# include "Character.h"

class					Map {
    public:
	Map(int size_x, int size_y);
	~Map();

	bool				AddCharacter(int id);
	bool 				RemoveCharacter(int id);
	bool 				FillBoard(std::string &board_string);
	bool				FillCharacters(std::string &board_string);
	Box 	 			**GetBoard() const;
	std::vector<Character> const&	GetCharacters() const;
	int 				GetSizeX() const;
	int				GetSizeY() const;
	Map&				operator=(Map const & other);

    private:
	int 				size_x;
	int 				size_y;
	Box 				**board;
	std::vector<Character>		characters;
};

#endif /* MAP_H_ */
