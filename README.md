## External Libraries

Configuration Properties | Path
--- | ---
C/C++ > General > Additional Include Directories | `$(SolutionDir)External_lib/GLEW/include`<br>`$(SolutionDir)External_lib/GLFW/include`<br>`$(SolutionDir)External_lib/GLM`<br>
Linker > General > Additional Library Directories Dependencies | `$(SolutionDir)External_lib/GLEW/lib/Release/Win32`<br>`$(SolutionDir)External_lib/GLFW/lib-vc2015`
Linker > Input > Additional Dependencies | `opengl32.lib`<br>`glfw3.lib`<br>`glew32.lib`

---

## Camera

#### Dependencies
`GL/glew.h` , `GLFW/glfw3.h` , `glm/glm.hpp` , `glm/gtc/matrix_transform.hpp`

#### Variables
access | type | name | purpose
--- | --- | --- | ---
`private` | `glm::vec3` | position | Current position of camera
`private` | `glm::vec3` | front | Direction vector indicating the direction player is facing
`private` | `glm::vec3` | up | Direction vector indicating the top of the player
`private` | `glm::vec3` | right | Direction vector indicating the right of the player
`private` | `glm::vec3` | worldUp | Direction vector of where the top of the world is
`private` | `GLfloat` | yaw | Rotation of camera about the z axis
`private` | `GLfloat` | pitch | Rotation of camera about the y axis 
`private` | `GLfloat` | moveSpeed | Movement speed
`private` | `GLfloat` | turnSpeed | Turning speedo

#### Constructors

parameter | purpose
--- | ---
`void` | Default constructor
`glm::vec3` startPosition<br>`glm::vec3` startUp<br>`GLfloat` startYaw<br>`GLfloat` startPitch<br>`GLfloat` startMoveSpeed<br>`GLfloat` startTurnSpeed | Comprehensive constructor which initialises variables

#### Methods

> private

return type | name | parameter | purpose
--- | --- | --- | --- 
`void` | update | `void` | Update `front` based on `yaw` & `pitch`<br>Update `right` based on `front` & `worldUp`<br>Update `up` based on `right` & `front`

> public

return type | name | parameter | purpose
--- | --- | --- | --- 
`void` | keyControl | `bool*` keys<br>`GLfloat` deltaTime | Set events based on keys.<br>Move player based on `deltaTime`
`void` | mouseControl | `GLfloat` xChange<br>`GLfloat` yChange | Change `pitch` and `yaw` based on mouse movement
`glm::mat4` | calculateViewMatrix | `void` | Using `glm::lookAt`, calculate view matrix<br>based on `position` , `position + front` & `up` 

#### Destructors

parameter | purpose
--- | ---
`void` | Default destructor

---

# Mesh

#### Dependencies
`GL/glew.h`

#### Variables
access | type | name | purpose
--- | --- | --- | ---
`private` | `GLuint` | VAO | **V**ertex **A**rray **O**bject. Stores information of a complete render object
`private` | `GLuint` | VBO | **V**ertex **B**uffer **O**bject. Memory buffer to hold 
`private` | `GLuint` | IBO | **I**ndex **B**uffer **O**bject. Store indexes of render object

#### Constructors

parameter | purpose
--- | ---
`void` | Default constructor

#### Methods

> public

return type | name | parameter | purpose
--- | --- | --- | --- 
`void` | create | `unsigned int` numOfVertices<br>`GLfloat*` vertices<br>`unsigned int` numOfIndices<br>`unsigned int*` indices | Generates VAO, IBO & VBO.<br>Assign vertices and indices data to buffers.<br>Sets Vertex Attribute Poitner.
`void` | render | `void` | Binds VAO and IBO and draws object.
`void` | clear | `void` | Deletes buffer and VAO, and set them to 0.

#### Destructors

parameter | purpose
--- | ---
`void` | Default destructor

---

# Shader

#### Dependencies
`stdio.h` , `string` , `fstream` , `GL/glew.h`

#### Variables
access | type | name | purpose
--- | --- | --- | ---
`private` | `GLuint` | ID | ID of shader program.
`private` | `GLuint` | uniformProjection | Location of projection matrix in shader.
`private` | `GLuint` | uniformModel | Location of model matrix in shader.
`private` | `GLuint` | uniformView | Location of view matrix in shader.

#### Constructors

parameter | purpose
--- | ---
`void` | Default constructor

#### Methods

> private

return type | name | parameter | purpose
--- | --- | --- | --- 
`void` | addShader | `GLuint` program<br>`const char*` code<br>`GLenum` type | Create shader of type.<br>Attach the source code.<br>Compile.<br>Attach to program.
`void` | compileShaders | `const char*` vertexCode<br>`const char*` fragmentCode | Create program.<br>Add shaders.<br>Link program.<br>Validate program.<br>Get location of matrices.
`std::string` | fileContents | `const char*` file | Returns content of `file`.

> public

return type | name | parameter | purpose
--- | --- | --- | --- 
`void` | create | `const char*` vertexFile<br>`const char*` fragmentFile | Gets code from files and compiles them.
`GLuint` | getProjectionLocation | `void` | Returns `uniformProjection`.
`GLuint` | getModelLocation | `void` | Returns `uniformModel`.
`GLuint` | getViewLocation | `void` | Returns `uniformView`.
`void` | use | `void` | Uses this program.
`void` | clear | `void` | Deletes program and sets variables to 0.

#### Destructors

parameter | purpose
--- | ---
`void` | Default destructor

---

# Window

#### Dependencies
`stdio.h` , `GL/glew.h` , `GLFW/glfw3.h`

#### Variables
access | type | name | purpose
--- | --- | --- | ---
`private` | `GLFWwindow*` | main | Main window.
`private` | `GLint` | width | Width of window.
`private` | `GLint` | height | Height of window.
`private` | `GLint` | bufferWidth | Buffer width of window.
`private` | `GLint` | bufferHeight | Buffer height of window.
`private` | `bool [1024]` | keys | State of keys.
`private` | `GLfloat` | lastX | Last X position of mouse.
`private` | `GLfloat` | lastY | Last Y position of mouse.
`private` | `GLfloat` | xChange | X difference from `lastX` and current X.
`private` | `GLfloat` | yChange | Y difference from `lastY` and current Y.
`private` | `bool` | mouseFirstMoved | Indicates if this is mouse first position.

#### Constructors

parameter | purpose
--- | ---
`void` | Default constructor
`GLint` w<br>`GLint` h | Initialise `width` & `height`

#### Methods

> private

return type | name | parameter | purpose
--- | --- | --- | --- 
`void` | createCallbacks | `void` | Sets key an cursor position callbacks.
`void` | `static` handleKeys | `GLFWwindow*` | Sets key an cursor position callbacks.

> public

return type | name | parameter | purpose
--- | --- | --- | --- 
`void` | create | `const char*` vertexFile<br>`const char*` fragmentFile | Gets code from files and compiles them.

#### Destructors

parameter | purpose
--- | ---
`void` | Default destructor

---