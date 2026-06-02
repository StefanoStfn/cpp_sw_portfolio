//
// Created by Martina on 01/06/2026.
//

#include "../include/relation_exp_wrapper.h"

namespace LPEngine
{
    // Unary negation
    RelationExpression operator- (const ColumnVector& col_vect_a)
    {
        auto tmp_exp = RelationExpression();
        std::cout << "Triggered - unary operator" << std::endl;
        return tmp_exp;
    }
    // Column vector interaction with coefficient
    RelationExpression operator* (double coefficient, const ColumnVector& col_vect)
    {
        auto tmp_exp = RelationExpression();
        std::cout << "Triggered * operator" << std::endl;
        std::cout << coefficient << std::endl;
        return tmp_exp;
    }

    RelationExpression operator* (const ColumnVector& col_vect, double coefficient)
    {
        return coefficient * col_vect;
    }

    // Column vector against column vector
    RelationExpression operator+ (const ColumnVector& col_vect_a, const ColumnVector& col_vect_b)
    {
        auto tmp_exp = RelationExpression();
        std::cout << "Triggered + operator" << std::endl;
        return tmp_exp;
    }

    RelationExpression operator- (const ColumnVector& col_vect_a, const ColumnVector& col_vect_b)
    {
        auto tmp_exp = RelationExpression();
        std::cout << "Triggered - operator" << std::endl;
        return tmp_exp;
    }

    // Column vector against RelationExpression
    RelationExpression operator+ (const ColumnVector& col_vect, const RelationExpression& lin_exp)
    {
        auto tmp_exp = RelationExpression();
        std::cout << "Triggered + operator" << std::endl;
        return tmp_exp;
    }

    RelationExpression operator+ (const RelationExpression& lin_exp, const ColumnVector& col_vect)
    {
        auto tmp_exp = RelationExpression();
        std::cout << "Triggered + operator" << std::endl;
        return tmp_exp;
    }

    RelationExpression operator- (const RelationExpression& lin_exp, const ColumnVector& col_vect)
    {
        auto tmp_exp = RelationExpression();
        std::cout << "Triggered - operator" << std::endl;
        return tmp_exp;
    }

    RelationExpression operator- (const ColumnVector& col_vect, const RelationExpression& lin_exp)
    {
        auto tmp_exp = RelationExpression();
        std::cout << "Triggered - operator" << std::endl;
        return tmp_exp;
    }

    // RelationExpression against RelationExpression
    RelationExpression operator+ (const RelationExpression& lin_exp_a, const RelationExpression& lin_exp_b)
    {
        auto tmp_exp = RelationExpression();
        std::cout << "Triggered + operator" << std::endl;
        return tmp_exp;
    }

    RelationExpression operator- (const RelationExpression& lin_exp_a, const RelationExpression& lin_exp_b)
    {
        auto tmp_exp = RelationExpression();
        std::cout << "Triggered - operator" << std::endl;
        return tmp_exp;
    }

    // Unary Negation for RelationExpression
    RelationExpression operator- (const RelationExpression& lin_exp)
    {
        auto tmp_exp = RelationExpression();
        std::cout << "Triggered - unary operator" << std::endl;
        return tmp_exp;
    }

    // Equality-Inequality
    RelationExpression operator>= (const RelationExpression& lin_exp, double coefficient)
    {
        auto tmp_exp = RelationExpression();
        std::cout << "Triggered >= operator" << std::endl;
        return tmp_exp;
    }
    RelationExpression operator<= (const RelationExpression& lin_exp, double coefficient)
    {
        auto tmp_exp = RelationExpression();
        std::cout << "Triggered <= operator" << std::endl;
        return tmp_exp;
    }
    RelationExpression operator== (const RelationExpression& lin_exp, double coefficient)
    {
        auto tmp_exp = RelationExpression();
        std::cout << "Triggered == operator" << std::endl;
        return tmp_exp;
    }
}