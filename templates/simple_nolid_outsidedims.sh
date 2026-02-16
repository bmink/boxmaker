#!/bin/zsh

WIDTH=5
DEPTH=2
HEIGHT=3
STOCK=0.344

cat << EOF
<svg xmlns="http://www.w3.org/2000/svg"
	width="24in" height="48in">

	<rect x="0in"
              y="1in"
              width="$(($WIDTH))in"
              height="$(($HEIGHT - $STOCK))in"
	      fill="#f0f0f0" stroke="black" />
	<text x="0.5in"
	      y="1in"
	      font-size="0.25in"
              fill="black"
              stroke="black">Front</text>

	<rect x="0in"
              y="$(($HEIGHT + 2))in"
              width="$(($WIDTH))in"
              height="$(($HEIGHT - $STOCK))in"
	      fill="#f0f0f0" stroke="black" />
	<text x="0.5in"
	      y="$(($HEIGHT + 2))in"
	      font-size="0.25in"
              fill="black"
              stroke="black">Back</text>

	<rect x="0in"
              y="$((($HEIGHT + 1) * 2 + 1))in"
              width="$(($DEPTH))in"
              height="$(($HEIGHT - $STOCK))in"
	      fill="#f0f0f0" stroke="black" />
	<text x="0.5in"
	      y="$((($HEIGHT + 1) * 2 + 1))in"
	      font-size="0.25in"
              fill="black"
              stroke="black">Side</text>

	<rect x="0in"
              y="$((($HEIGHT + 1) * 3 + 1))in"
              width="$(($DEPTH))in"
              height="$(($HEIGHT - $STOCK))in"
	      fill="#f0f0f0" stroke="black" />
	<text x="0.5in"
	      y="$((($HEIGHT + 1) * 3 + 1))in"
	      font-size="0.25in"
              fill="black"
              stroke="black">Side</text>

	<rect x="0in"
              y="$((($HEIGHT + 1) * 4 + 1))in"
              width="$(($WIDTH - 2 * $STOCK))in"
              height="$(($DEPTH - 2 * $STOCK))in"
	      fill="#f0f0f0" stroke="black" />
	<text x="0.5in"
	      y="$((($HEIGHT + 1) * 4 + 1))in"
	      font-size="0.25in"
              fill="black"
              stroke="black">Bottom</text>

</svg>
EOF
