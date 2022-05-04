<h2>LRU Page Replacement Algorithm using Splay Trees</h2>
<p>LRU works on the idea that the pages that have been most heavily used in the past are most likely to be used heavily in the future too. So, whenever page replacement happens, the page which has not been used for the longest amount of time is replaced. LRU benefits by being immune to Belady’s Anomaly. For sufficiently long access sequence, splay trees are effective. Hence, for better performance in comparison to traditional algorithm, LRU algorithm has been implemented using splay trees. For this algorithm, there is ‘Turn’ information, associated with every page. ‘Turn’ indicates number of times a page has been accessed. And a page with minimum turn considers as a least recently used page.</p>

<br><h2>Table of contents</h2>
<ul>
    <li>Operations and Functions</li>
    <li>Installation</li>
    <li>Technologies</li>
</ul>

<br><h2>Operations</h2>
<ul>
    <li>Insert</li>
    <li>Splay</li>
    <li>Delete</li>
    <li>Search</li>
  </ul>
  <br><br>Overview of above mentioned operations:
<ul>
    <li>Insert: This operation inserts a node (containing reference_no of the page) into the tree in BST fashion and splay the inserted node to the root's position</li>
    <li>Splay: Splay operation, according to the position of the given node performs either of the six rotations (Left, Right, Left-Left, Right-Right, Left-Right, Right-Left) to bring the given node to the root's position</li>
    <li>Delete: It splays the node with minimum 'turn' at the root's position, deletes the node, dividing the tree into two halves i.e Left Subtree and Right Subtree,
  It joins the two halves by making the node with maximum key from left subtree as root and making the right subtree as newly selected root's right child</li>
  <li>Search: This Operation, searches the node with given key (page no) and returns the corresponding node link</li>
</ul>

<br><h2>Installation</h2>
For cloning the repository from git bash,<br>
***git clone https://github.com/mcbiswas24/LRU_PR_using_splaytrees***<br><br>
for cloning the repository from github,<br>
***Click on 'Code' option, select 'Download Zip'***<br><br><br>
After cloning the repository,<br>
<ul>
  <li>Double click on 'LRU_splaytrees.exe' to directly execute the code</li>
  <li>or click on 'LRU_splaytrees.c' to open and execute code from an editor </li>
 </ul>
  
<br><h2>Technologies</h2>
Project is created using C language:
<ul>
    <li>gcc version 6.3.0</li>
    <li>Thread model: win32</li>
</ul>


<br><h2>Contributors</h2>
<ul>
    <li>Mahima Biswas</li>
    <li>Neer Choksi</li>
    <li>Shreyal Shah</li>
</ul>
