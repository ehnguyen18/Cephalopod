/*
 * Cell.h
 *
 *  Created on: 27 Feb 2022
 *      Author: dongmo
 */

#ifndef CELL_H_
#define CELL_H_

struct Cell {
	int x;
	int y;
	int value;
	double heuristic;

	Cell (){
		x=0;
		y=0;
		value=0;
		heuristic=0;
	}
	Cell(int xx, int yy, int v): x(xx), y(yy), value(v) {}
	Cell(int xx , int yy, double hh):x(xx), y(yy), heuristic(hh) {}

	bool operator<(const Cell& c) const {
		return heuristic < c.heuristic;
	}

};



#endif /* CELL_H_ */
