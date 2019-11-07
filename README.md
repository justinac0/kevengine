<header>
    <h1>Kevin Engine</h1>
    <p>This project is an exploration into game engine development.</p>
    <p>This project is written in C and is licensed under the <a href="http://unlicense.org">Unlicense</a>.</p>
    <p>The following links present the third party libraries used in the development of this project.</p>
    <nav>
        <ul>
            <li><a href="https://github.com/Dav1dde/glad">glad</a></li>
            <li><a href="https://www.glfw.org/">glfw 3.3</a></li>
        </ul>
    </nav>
</header>

<h2>Contents</h2>
<div>
  <nav>
    <ul><li><strike>Website</strike></li></ul>
    <ul><li><a href="#build-source">Build Source</a></li></ul>
  </nav>
</div>

  <div id="build-source">
      <h2>Building Source</h2>
      <p>The following sub-sections cover how to setup the build system and how to compile the <code>kevin-engine</code> source.</p>
      <div>
          <h2>Windows Setup</h2>
<pre>You will need to download the GLFW binaries from this following <a href="https://www.glfw.org/download.html">link</a>.

  For compiling on windows we use MinGW (install gcc options)
  http://mingw.org/

  Extract the GLFW binary files -> open containing folder 'lib-mingw-w64' or 'lib-mingw32-w32'
  Inside you will see 3 files: 'glfw3.dll', 'libglfw3.a' and 'libglfw3dll.a'
  Copy these files and place then inside of the folder 'lib' found inside of the MinGW installation path.
  <code>
      MinGW
      ├───bin                              
      ├───include                          
      ├───lib                              
      │   └─  ** Copied Files **                   
      ├───libexec 
      ├───mingw32
      ├───share
      └───var    
  </code>
</pre>
          <h2>Compiling on Windows</h2>
<pre>
  For compilation run <code>mingw32-make all</code>
  The executable can be found in the bin folder of kevin-engine <code>bin/kevin.exe</code>
  For removing generated files run <code>mingw32-make clean</code>
</pre>
      </div>

  <div>
      <h2>Linux Setup</h2>

<pre>
  You will need to install a couple of packages:
  'make', 'libgl1-mesa-dev' and 'gcc'
</pre>
<h2>Linux Compilation</h2>
<pre>
  For compilation run 'make all'
  The executable can be found in the bin folder of kevin-engine 'bin/kevin'
  For removing generated files run 'make clean'
</pre>
  </div>
