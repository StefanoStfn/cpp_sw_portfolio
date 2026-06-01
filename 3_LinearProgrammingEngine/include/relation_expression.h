//
// Created by Martina on 01/06/2026.
//

#ifndef INC_3_LINEARPROGRAMMINGENGINE_RELATION_EXPRESSION_H
#define INC_3_LINEARPROGRAMMINGENGINE_RELATION_EXPRESSION_H

#pragma once

namespace LPEngine
{
    class RelationExpression
    {

    };

    RelationExpression operator+ (double coefficient, RelationExpression& lin_exp);
    RelationExpression operator- (double coefficient, RelationExpression& lin_exp);
    RelationExpression operator+ (RelationExpression& lin_exp, double coefficient);
    RelationExpression operator- (RelationExpression& lin_exp, double coefficient);
    // Equality-Inequality
    RelationExpression operator>= (RelationExpression& lin_exp, double coefficient);
    RelationExpression operator<= (RelationExpression& lin_exp, double coefficient);
    RelationExpression operator== (RelationExpression& lin_exp, double coefficient);
}


#endif //INC_3_LINEARPROGRAMMINGENGINE_RELATION_EXPRESSION_H
