#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Point {
    float x;
    float y;
} Point;

typedef struct Node {
    Point point;
    char discriminator;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(Point point) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->point = point;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insertNode(Node* root, Point point, int depth) {
    if (root == NULL) {
        return createNode(point);
    }

    int currentDepth = depth % 2; // Alternates between x and y coordinates

    if (currentDepth == 0) {
        if (point.x < root->point.x) {
            root->left = insertNode(root->left, point, depth + 1);
        } else {
            root->right = insertNode(root->right, point, depth + 1);
        }
    } else {
        if (point.y < root->point.y) {
            root->left = insertNode(root->left, point, depth + 1);
        } else {
            root->right = insertNode(root->right, point, depth + 1);
        }
    }

    return root;
}

double distance(Point p1, Point p2) {
    int dx = p1.x - p2.x;
    int dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}

Point findNearestNeighbor(Node* root, Point target, int depth, double* minDistance, Point nearestPoint) {
    if (root == NULL) {
        return nearestPoint;
    }

    double currentDistance = distance(root->point, target);

    if (currentDistance < *minDistance) {
        *minDistance = currentDistance;
        nearestPoint = root->point;
    }

    int currentDepth = depth % 2; // Alternates between x and y coordinates

    Node* nearSubtree = NULL;
    Node* farSubtree = NULL;

    if (currentDepth == 0) {
        if (target.x < root->point.x) {
            nearSubtree = root->left;
            farSubtree = root->right;
        } else {
            nearSubtree = root->right;
            farSubtree = root->left;
        }
    } else {
        if (target.y < root->point.y) {
            nearSubtree = root->left;
            farSubtree = root->right;
        } else {
            nearSubtree = root->right;
            farSubtree = root->left;
        }
    }

    nearestPoint = findNearestNeighbor(nearSubtree, target, depth + 1, minDistance, nearestPoint);

    if (currentDepth == 0 && fabs(target.x - root->point.x) < *minDistance) {
        nearestPoint = findNearestNeighbor(farSubtree, target, depth + 1, minDistance, nearestPoint);
    }

    if (currentDepth == 1 && fabs(target.y - root->point.y) < *minDistance) {
        nearestPoint = findNearestNeighbor(farSubtree, target, depth + 1, minDistance, nearestPoint);
    }

    return nearestPoint;
}

/* int main() {
    Node* root = NULL;
    Node* aux;
    Point p[3] = {{ -16.7573, -49.4412 }, { -18.4831, -47.3916 }, { -16.197, -48.7057 }};

    root = insertNode(root, p[0], 0);
    root = insertNode(root, p[1], 0);
    root = insertNode(root, p[2], 0);

    double minDistance = distance(root->point, p[3]);
    Point nearestPoint = root->point;

    nearestPoint = findNearestNeighbor(root, p[3], 0, &minDistance, nearestPoint);

    printf("kd-tree:\n");
    printf("(%.4f, %.4f)", nearestPoint.x, nearestPoint.y);

    return 0;
}
 */