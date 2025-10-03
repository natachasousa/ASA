"""
Program that calculates the maximum daily profit achievable from the production
and sale of Christmas toys at UbiquityInc.

Alunas: Beatiz Martinho (106835), Natacha Sousa (107413)
"""

from pulp import LpProblem, LpMaximize, LpVariable, lpSum, GLPK, LpInteger, value

t, p, max_producao = map(int, input().split())

x = {}  # Variables for toys
toys = {}
for i in range(t):
    profit, capacity = map(int, input().split())
    toys[i] = {'l': profit, 'c': capacity}
    x[i] = LpVariable(f"x{i}", 0, toys[i]['c'], LpInteger)

y = {}  # Variables for packages
packs = {}
for i in range(p):
    items_and_profit = list(map(int, input().split()))
    items, profit = items_and_profit[:-1], items_and_profit[-1]
    packs[i] = {'items': items, 'p': profit}
    y[i] = LpVariable("y%d" % i, 0, None, LpInteger)

# Inicialize problem
problem = LpProblem("Max Profit Problem", LpMaximize)

# The objective function
toy_profits = [toys[i]['l'] for i in range(t)]
problem += lpSum([x[i] * toy_profits[i] for i in range(t)]) + lpSum([y[i] * (packs[i]['p'] - lpSum([toy_profits[toy - 1] for toy in packs[i]['items']])) for i in range(p)])

# Constraint: production limit
problem += lpSum(x.values()) <= max_producao

# Constraint: package production limit per toy
pack_items_set = [set(packs[i]['items']) for i in range(p)]
for i in range(t):
    problem += x[i] >= lpSum([y[j] for j in range(p) if i + 1 in pack_items_set[j]])

# Solve problem
solver = GLPK(msg=0) 
max_profit = problem.solve(solver)
print(value(problem.objective))