#ifndef BOX_H_
# define BOX_H_

class		Box {
    public:
	Box();
	~Box();

	int 	GetFood() const;
	void 	SetFood(int food);

    private:
	int	food = 0;
};

#endif /* BOX_H_ */
