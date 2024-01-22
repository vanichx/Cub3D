#include <stdio.h>

// Data structure representing a 2D point
typedef struct {
	double x;
	double y;
} Point;

// Data structure representng a 2D line segment
typedef struct {
	Point start;
	Point end;
} Segment;

// Function to calculate the winding number for a point with respect to a curve
int calculateWindingNumber(Point point, Segment curve[], int numSegments)
{
	int windingNumber = 0;

	// iterate through each segment of the curve
	for (int i = 0; i < numSegments; i++)
	{
		Point start = curve[i].start;
		Point end = curve[i].end;

		// Check if the ray from the point intersects with the current segment
		if ((start.y <= point.y && end.y > point.y) || (end.y <= point.y && start.y > point.y))
		{
			// Calculate the intersection point's x-coordinate on the ray
			double intersectionX = (point.y - start.y) / (end.y - start.y) * (end.x - start.x) + start.x;

			// Check if the intersection point is to the right of the point
			if (point.x < intersectionX)
			{
				// Update wwinding number based on the direction of the curve segment
				if (start.y > end.y)
				{
					windingNumber--;
				}
				else
				{
					windingNumber++;
				}
			}
		}
	}
	return windingNumber;
}

int main() {
	// Example usage
	Point point = {1.5, 2.0};  // Given point P
	Segment curve[] = {{{1.0, 1.0}, {2.0, 3.0}}, {{2.0, 3.0}, {3.0, 1.0}}, {{3.0, 1.0}, {1.0, 1.0}}};
	int numSegments = sizeof(curve) / sizeof(curve[0]);

	// Calculate the winding number
	int windingNumber = calculateWindingNumber(point, curve, numSegments);

	// Determine whether the point is inside or outsede the curve
	if (windingNumber != 0)
	{
		printf("Point is inside the curve with winding number: %d\n", windingNumber);
	}
	else
	{
		printf("Point is outside the curve\n");
	}
	return 0;
}