# search.py
# ---------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


"""
In search.py, you will implement generic search algorithms which are called by
Pacman agents (in searchAgents.py).
"""

import util


class SearchProblem:
    """
    This class outlines the structure of a search problem, but doesn't implement
    any of the methods (in object-oriented terminology: an abstract class).

    You do not need to change anything in this class, ever.
    """

    def getStartState(self):
        """
        Returns the start state for the search problem.
        """
        util.raiseNotDefined()

    def isGoalState(self, state):
        """
          state: Search state

        Returns True if and only if the state is a valid goal state.
        """
        util.raiseNotDefined()

    def getSuccessors(self, state):
        """
          state: Search state

        For a given state, this should return a list of triples, (successor,
        action, stepCost), where 'successor' is a successor to the current
        state, 'action' is the action required to get there, and 'stepCost' is
        the incremental cost of expanding to that successor.
        """
        util.raiseNotDefined()

    def getCostOfActions(self, actions):
        """
         actions: A list of actions to take

        This method returns the total cost of a particular sequence of actions.
        The sequence must be composed of legal moves.
        """
        util.raiseNotDefined()


def tinyMazeSearch(problem):
    """
    Returns a sequence of moves that solves tinyMaze.  For any other maze, the
    sequence of moves will be incorrect, so only use this for tinyMaze.
    """
    from game import Directions
    s = Directions.SOUTH
    w = Directions.WEST
    return [s, s, w, s, w, w, s, w]


def depthFirstSearch(problem):
    """
    Search the deepest nodes in the search tree first.

    Your search algorithm needs to return a list of actions that reaches the
    goal. Make sure to implement a graph search algorithm.

    To get started, you might want to try some of these simple commands to
    understand the search problem that is being passed in:

    print("Start:", problem.getStartState())
    print("Is the start a goal?", problem.isGoalState(problem.getStartState()))
    print("Start's successors:", problem.getSuccessors(problem.getStartState()))
    """
    "*** YOUR CODE HERE ***"
    open = util.Stack()
    open.push(problem.getStartState())#初始节点入栈
    close = {}
    pre = {}
    ans = []
    while not open.isEmpty():
        u = open.pop()
        if u in close:
            continue
        close[u] = True
        if problem.isGoalState(u):#如果节点是目标节点，根据路径记录返回到初始节点并记录路径
            p = u
            while p in pre:
                fa, Dir = pre[p]
                ans.append(Dir)
                p = fa
            ans.reverse()
            break
        for v, dir, cost in problem.getSuccessors(u):#得到后继节点
            if v in close:#如果当前节点已在close表中，则直接退出
                continue
            pre[v] = (u, dir)#记录扩展节点的父节点
            open.push(v)
    return ans
    # util.raiseNotDefined()


def breadthFirstSearch(problem):
    """Search the shallowest nodes in the search tree first."""
    "*** YOUR CODE HERE ***"
    open = util.Queue()
    open.push(problem.getStartState())#初始节点入队列
    close = {}
    pre = {}
    ans = []
    close[problem.getStartState()] = True
    while not open.isEmpty():
        u = open.pop()
        if problem.isGoalState(u):#如果节点是目标节点，根据路径记录返回到初始节点并记录路径
            p = u
            while p in pre:
                fa, Dir = pre[p]
                ans.append(Dir)
                p = fa
            ans.reverse()
            break
        for v, dir, cost in problem.getSuccessors(u):#得到后继节点
            if v in close:#如果当前节点已在close表中，则直接退出
                continue
            close[v] = True
            pre[v] = (u, dir)#记录扩展节点的父节点
            open.push(v)
    return ans
    # util.raiseNotDefined()


def uniformCostSearch(problem):
    """Search the node of least total cost first."""
    "*** YOUR CODE HERE ***"
    open = util.PriorityQueue()
    open.push((problem.getStartState(), 0), 0)#初始节点入优先队列
    close = {}
    pre = {}
    ans = []
    close[problem.getStartState()] = 0
    while not open.isEmpty():
        u, w = open.pop()
        if w > close[u]:
            continue
        if problem.isGoalState(u):#如果节点是目标节点，根据路径记录返回到初始节点并记录路径
            p = u
            while p in pre:
                fa, Dir = pre[p]
                ans.append(Dir)
                p = fa
            ans.reverse()
            break
        for v, dir, cost in problem.getSuccessors(u):#得到后继节点
            if v in close and w + cost >= close[v]:#如果当前节点已在close表中并且代价比目标节点大，则直接退出
                continue
            close[v] = w + cost
            pre[v] = (u, dir)#记录扩展节点的父节点
            open.push((v, w + cost), w + cost)
    return ans
    # util.raiseNotDefined()


def nullHeuristic(state, problem=None):
    """
    A heuristic function estimates the cost from the current state to the nearest
    goal in the provided SearchProblem.  This heuristic is trivial.
    """
    return 0


def aStarSearch(problem, heuristic=nullHeuristic):
    """Search the node that has the lowest combined cost and heuristic first."""
    "*** YOUR CODE HERE ***"
    open = util.PriorityQueue()
    open.push((problem.getStartState(), 0), heuristic(problem.getStartState(), problem))#初始节点入优先队列
    close = {}
    pre = {}
    ans = []
    close[problem.getStartState()] = 0
    while not open.isEmpty():
        u, w = open.pop()
        if w > close[u]:
            continue
        if problem.isGoalState(u):#如果节点是目标节点，根据路径记录返回到初始节点并记录路径
            p = u
            while p in pre:
                fa, Dir = pre[p]
                ans.append(Dir)
                p = fa
            ans.reverse()
            break
        for v, dir, cost in problem.getSuccessors(u):#得到后继节点
            if v in close and w + cost >= close[v]:#如果当前节点已在close表中并且代价比目标节点大，则直接退出
                continue
            close[v] = w + cost
            pre[v] = (u, dir)#记录扩展节点的父节点
            open.push((v, w + cost), w + cost + heuristic(v, problem))#在优先队列中比较的参数需要加上代价函数
    return ans
    # util.raiseNotDefined()


# Abbreviations
bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
ucs = uniformCostSearch
