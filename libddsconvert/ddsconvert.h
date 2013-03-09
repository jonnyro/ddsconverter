enum CompressionStrategyType
{
	RGBA8888,
	DDS_DXT5,
	DDS_DXT3,
	DDX_DXT1,
	DDS_DXT5_MIPMAP,
	DDS_DXT3_MIPMAP,
	DDS_DXT1_MIPMAP
};

class Image
{
	public:

		Image(const char* filename);
		unsigned const char* GetImageData;
		unsigned int GetDepth();
};

class MipMappedImage
{
	size_t  _mipLevels;
	unsigned char **_mipMaps;
	bool _mipMapsUpdated;

	public:
		void generate_mip_maps();
		size_t get_lod_count();
};

class DDSImage : protected MipMappedImage
{
	private:
		CompressionStrategyType _compression_strategy;
	public:
		void compress();
		unsigned const char *GetCompressedData(unsigned int _lod);
};


