# *<p align="center">Kodi development</p>*
-------------
*<p align="center">
  [<img src="http://kodi.wiki/images/c/c9/Logo.png" alt="Home">](http://kodi.tv/)
  [<img src="http://kodi.wiki/images/5/52/Zappy.png" alt="Home" width="100" height="100">](http://kodi.tv/)
</p>*
*<p align="center">
  [<img src="help.BackButton.png" alt="Back" width="100" height="40">](../Readme.md#StreamUtils)
</p>*
#### *<p align="center">Group: `Stream utilities`</p>*

----------

The with #include `<kodi/pvr.api2/StreamUtils.h>` given functions are basically used to allow add-on access to Kodi's functions

Classes
-------------

#### <a id="CStreamProperties"></a>Class: `CStreamProperties::CStreamProperties(...);`

*  **`CStreamProperties()`**
    * Constructor

*  **`virtual ~CStreamProperties();`**
    * Destructor

*  **`void Clear(void);`**
    * Resets the streams

*  **`int GetStreamId(unsigned int iPhysicalId) const;`**
    * Returns the index of the stream with the specified physical ID, or -1 if there no stream is found. This method is called very often which is why we keep a separate map for this.
        * **`iPhysicalId`** Identifier for stream data to get
        * **return:**The used class id for it

* `CPVRStream* GetStreamById(unsigned int iPhysicalId) const;`**
    * Returns the stream with the specified physical ID, or null if no such stream exists
        * **`iPhysicalId`** Identifier for stream data to get
        * **return:** Return pointer of stream to get

*  **`void GetStreamData(unsigned int iPhysicalId, CPVRStream* stream);`**
    * Populates the specified stream with the stream having the specified physical ID. If the stream is not found only target stream's physical ID will be populated.
        * **`iPhysicalId`** Identifier for stream data to get
        * **`stream`** Return pointer of stream to get

*  **`bool GetProperties(PVR_STREAM_PROPERTIES* props);`**
    * Populates props with the current streams and returns whether there are any streams at the moment or not.
        * **`props`**  Pointer where present properties becomes stored
        * **return:** True if success

*  **`void UpdateStreams(stream_vector &newStreams);`**
    *  Merges new streams into the current list of streams. Identical streams will retain their respective indexes and new streams will replace unused indexes or be appended.
        * **`newStreams`**  Pointer to pass to set streams array

-------------
#### <a id="CPVRStream"></a>Class: `CPVRStream::CPVRStream(...);`

*  **`CPVRStream()`**
    * Constructor

*  **`CPVRStream(const CPVRStream &other)`**
    * Constructor to generate copy of given class

*  **`~CPVRStream();`**
    * Destructor

*  **`bool operator==(const CPVRStream &other) const;`**
    * Compares this stream based on another stream
        * **`other`**  The other stream to compare
        * **return:** true if equal

*  **` bool operator<(const CPVRStream &other) const;`**
    * Compares this stream with another one so that video streams are sorted before any other streams and the others are sorted by the physical ID
        * **`other`**  The other stream to compare
        * **return:** true if before

*  **`void Clear();`**
    * Clears the stream

*  **`bool IsCleared() const;`**
    * Checks whether the stream has been cleared
        * **return:** True if cleared
