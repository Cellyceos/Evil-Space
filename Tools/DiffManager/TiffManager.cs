using System;
using System.IO;
using System.Drawing;
using System.Drawing.Imaging;		 
using System.Collections;

namespace DiffManager
{
	/// <summary>
	/// Summary description for TiffManager.
	/// </summary>
	public class TiffManager : IDisposable
	{
		private string imageFileName;
		private int number;
		private readonly Image image;
		private string tempWorkingDir;

		public TiffManager(string imageFileName)
		{
			this.imageFileName=imageFileName;
			image=Image.FromFile(this.imageFileName);
			GetPageNumber();
		}
		
		public TiffManager(){
		}

		/// <summary>
		/// Read the image file for the page number.
		/// </summary>
		private void GetPageNumber(){
			Guid objGuid=image.FrameDimensionsList[0];
			var objDimension=new FrameDimension(objGuid);

			//Gets the total number of frames in the .tiff file
			number=image.GetFrameCount(objDimension);
		}

		/// <summary>
		/// Read the image base string,
		/// Assert(GetFileNameStartString(@"c:\test\abc.tif"),"abc")
		/// </summary>
		/// <returns></returns>
		private string GetFileNameStartString(){
			int posDot=imageFileName.LastIndexOf(".");
			int posSlash=imageFileName.LastIndexOf(@"\");
			return imageFileName.Substring(posSlash+1,posDot-posSlash-1);
		}

		/// <summary>
		/// This function will output the image to a TIFF file with specific compression format
		/// </summary>
		/// <param name="outPutDirectory">The splited images' directory</param>
		/// <param name="format">The codec for compressing</param>
		/// <returns>splited file name array list</returns>
		public ArrayList SplitTiffImage(string outPutDirectory,EncoderValue format)
		{
			string fileStartString=outPutDirectory+"\\"+GetFileNameStartString();
			var splitedFileNames=new ArrayList();
		    Guid objGuid=image.FrameDimensionsList[0];
		    var objDimension=new FrameDimension(objGuid);

		    //Saves every frame as a separate file.
		    Encoder enc=Encoder.Compression;
		    int curFrame=0;
		    for (int i=0;i<number;i++)
		    {
		        image.SelectActiveFrame(objDimension,curFrame);
		        var ep=new EncoderParameters(1);
		        ep.Param[0]=new EncoderParameter(enc,(long)format);
		        ImageCodecInfo info=GetEncoderInfo("image/tiff");
					
		        //Save the master bitmap
		        string fileName=string.Format("{0}{1}.TIF",fileStartString,i);
		        image.Save(fileName,info,ep);
		        splitedFileNames.Add(fileName);

		        curFrame++;
		    }

		    return splitedFileNames;
		}

		/// <summary>
		/// This function will join the TIFF file with a specific compression format
		/// </summary>
		/// <param name="imageFiles">string array with source image files</param>
		/// <param name="outFile">target TIFF file to be produced</param>
		/// <param name="compressEncoder">compression codec enum</param>
		/// <param name="ratio"></param>
		public void JoinTiffImages(string[] imageFiles,string outFile,EncoderValue compressEncoder, float ratio)
		{
		    //If only one page in the collection, copy it directly to the target file.
		    if (imageFiles.Length==1)
		    {
		        File.Copy(imageFiles[0],outFile,true);
		        return;
		    }

		    //use the save encoder
		    Encoder enc=Encoder.SaveFlag;

		    var ep=new EncoderParameters(2);
		    ep.Param[0]=new EncoderParameter(enc,(long)EncoderValue.MultiFrame); 
		    ep.Param[1] = new EncoderParameter(Encoder.Compression,(long)compressEncoder); 

		    Bitmap pages = null;
		    int frame=0;
		    ImageCodecInfo info=GetEncoderInfo("image/tiff");


		    foreach(string strImageFile in imageFiles)
		    {
                var img = Image.FromFile(strImageFile);
                var nWidth = (int)(img.Width * ratio);
                var nHeight = (int)(img.Height * ratio);
                var size = new Size(nWidth, nHeight);

                if (frame == 0)
                {
                    pages = new Bitmap(img, size);
                    //save the first frame
                    pages.Save(outFile, info, ep);
                }
                else
                {
                    //save the intermediate frames
                    ep.Param[0] = new EncoderParameter(enc, (long)EncoderValue.FrameDimensionPage);

                    var bm = new Bitmap(img, size);
                    if (pages != null) pages.SaveAdd(bm, ep);
                }

                if (frame == imageFiles.Length - 1)
                {
                    //flush and close.
                    ep.Param[0] = new EncoderParameter(enc, (long)EncoderValue.Flush);
                    if (pages != null) pages.SaveAdd(ep);
                }

		        frame++;
		    }

		    return;
		}

		/// <summary>
		/// This function will join the TIFF file with a specific compression format
		/// </summary>
		/// <param name="imageFiles">array list with source image files</param>
		/// <param name="outFile">target TIFF file to be produced</param>
		/// <param name="compressEncoder">compression codec enum</param>
        /// <param name="ratio"></param>
        public void JoinTiffImages(ArrayList imageFiles, string outFile, EncoderValue compressEncoder, float ratio)
		{
			try
			{
				//If only one page in the collection, copy it directly to the target file.
				if (imageFiles.Count==1){
					File.Copy((string)imageFiles[0],outFile,true);
					return;
				}

				//use the save encoder
				Encoder enc=Encoder.SaveFlag;

				var ep=new EncoderParameters(2);
				ep.Param[0]=new EncoderParameter(enc,(long)EncoderValue.MultiFrame); 
				ep.Param[1] = new EncoderParameter(Encoder.Compression,(long)compressEncoder);

                Bitmap pages = null;
                int frame = 0;
                ImageCodecInfo info = GetEncoderInfo("image/tiff");


                foreach (string strImageFile in imageFiles)
                {
                    var img = Image.FromFile(strImageFile);
                    var nWidth = (int)(img.Width * ratio);
                    var nHeight = (int)(img.Height * ratio);
                    var size = new Size(nWidth, nHeight);

                    if (frame == 0)
                    {
                        pages = new Bitmap(img, size);
                        //save the first frame
                        pages.Save(outFile, info, ep);
                    }
                    else
                    {
                        //save the intermediate frames
                        ep.Param[0] = new EncoderParameter(enc, (long)EncoderValue.FrameDimensionPage);

                        var bm = new Bitmap(img, size);
                        if (pages != null) pages.SaveAdd(bm, ep);
                    }

                    if (frame == imageFiles.Count - 1)
                    {
                        //flush and close.
                        ep.Param[0] = new EncoderParameter(enc, (long)EncoderValue.Flush);
                        if (pages != null) pages.SaveAdd(ep);
                    }

                    frame++;
				}
			}
			catch (Exception ex)
			{
#if DEBUG
				Console.WriteLine(ex.Message);
#endif
				throw;
			}
			
			return;
		}

	    /// <summary>
	    /// Remove a specific page within the image object and save the result to an output image file.
	    /// </summary>
	    /// <param name="pageNumber">page number to be removed</param>
	    /// <param name="compressEncoder">compress encoder after operation</param>
	    /// <param name="strFileName">filename to be outputed</param>
	    /// <param name="ratio"></param>
	    public void RemoveAPage(int pageNumber, EncoderValue compressEncoder, string strFileName, float ratio)
        {
		    //Split the image files to single pages.
		    ArrayList arrSplited=SplitTiffImage(tempWorkingDir,compressEncoder);
				
		    //Remove the specific page from the collection
		    string strPageRemove=string.Format("{0}\\{1}{2}.TIF",tempWorkingDir,GetFileNameStartString(),pageNumber);
		    arrSplited.Remove(strPageRemove);

            JoinTiffImages(arrSplited, strFileName, compressEncoder, ratio);

		    return;
		}

		/// <summary>
		/// Getting the supported codec info.
		/// </summary>
		/// <param name="mimeType">description of mime type</param>
		/// <returns>image codec info</returns>
		private static ImageCodecInfo GetEncoderInfo(string mimeType){
			ImageCodecInfo[] encoders=ImageCodecInfo.GetImageEncoders();
			foreach (ImageCodecInfo t in encoders)
			{
			    if (t.MimeType==mimeType)
			        return t;
			}

		    throw new Exception( mimeType + " mime type not found in ImageCodecInfo" );
		}

		/// <summary>
		/// Return the memory steam of a specific page
		/// </summary>
		/// <param name="pageNumber">page number to be extracted</param>
		/// <returns>image object</returns>
		public Image GetSpecificPage(int pageNumber)
		{
			MemoryStream ms=null;
			Image retImage=null;
			try
			{
                ms=new MemoryStream();
				Guid objGuid=image.FrameDimensionsList[0];
				var objDimension=new FrameDimension(objGuid);

				image.SelectActiveFrame(objDimension,pageNumber);
				image.Save(ms,ImageFormat.Png);
				
				retImage=Image.FromStream(ms);

				return retImage;
			}
			catch (Exception)
			{
			    if (ms != null) ms.Close();
			    if (retImage != null) retImage.Dispose();
			    throw;
			}
		}

		/// <summary>
		/// Convert the existing TIFF to a different codec format
		/// </summary>
		/// <param name="strNewImageFileName"></param>
		/// <param name="compressEncoder"></param>
		/// <param name="ratio"></param>
		/// <returns></returns>
        public void ConvertTiffFormat(string strNewImageFileName, EncoderValue compressEncoder, float ratio)
		{
			//Split the image files to single pages.
			ArrayList arrSplited=SplitTiffImage(tempWorkingDir,compressEncoder);
			JoinTiffImages(arrSplited,strNewImageFileName,compressEncoder, ratio);

			return;
		}

		/// <summary>
		/// Image file to operate
		/// </summary>
		public string ImageFileName
		{
			get
			{
				return imageFileName;
			}
			set{
				imageFileName=value;
			}
		}

		/// <summary>
		/// Buffering directory
		/// </summary>
		public string TempWorkingDir
		{
			get
			{
				return tempWorkingDir;
			}
			set{
				tempWorkingDir=value;
			}
		}

		/// <summary>
		/// Image page number
		/// </summary>
		public int Number
		{
			get
			{
				return number;
			}
		}

	
		#region IDisposable Members

		public void Dispose()
		{
            if (image != null)
                image.Dispose();

			GC.SuppressFinalize(this);
		}

		#endregion
	}
}
