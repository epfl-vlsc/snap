cmake_minimum_required(VERSION 3.6)
project(snap)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories(SNAPLib)

set(SOURCE_FILES
#    apps/ComputeROC/ComputeROC.cpp
#    apps/ComputeROC/stdafx.cpp
#    apps/ComputeROC/stdafx.h
#    apps/ComputeROC/targetver.h
#    apps/DistanceHist/DistanceHist.cpp
#    apps/DistanceHist/stdafx.cpp
#    apps/DistanceHist/stdafx.h
#    apps/DistanceHist/targetver.h
#    apps/DistanceHist/WGsim.h
#    apps/ExtractReads/ExtractReads.cpp
#    apps/ExtractReads/stdafx.cpp
#    apps/ExtractReads/stdafx.h
#    apps/ExtractReads/targetver.h
#    apps/RandomizePIfastq/GoodRandom.cpp
#    apps/RandomizePIfastq/GoodRandom.h
#    apps/RandomizePIfastq/RandomizePIfastq.cpp
#    apps/RandomizePIfastq/stdafx.cpp
#    apps/RandomizePIfastq/stdafx.h
#    apps/RandomizePIfastq/targetver.h
#    apps/snap/Main.cpp
#    apps/snap/stdafx.cpp
#    apps/snap/stdafx.h
#    apps/SNAPCommand/SNAPCommand.cpp
#    apps/SNAPCommand/stdafx.cpp
#    apps/SNAPCommand/stdafx.h
#    apps/stringz/GoodRandom.cpp
#    apps/stringz/GoodRandom.h
#    apps/stringz/stdafx.cpp
#    apps/stringz/stdafx.h
#    apps/stringz/stringz.cpp
#    apps/stringz/targetver.h
#    apps/ToFASTQ/stdafx.cpp
#    apps/ToFASTQ/stdafx.h
#    apps/ToFASTQ/ToFASTQ.cpp
#    apps/wc/stdafx.cpp
#    apps/wc/stdafx.h
#    apps/wc/targetver.h
#    apps/wc/wc.cpp
#    import/pdclibhdfs/inc/exception.h
#    import/pdclibhdfs/inc/expect.h
#    import/pdclibhdfs/inc/hdfs.h
#    import/pdclibhdfs/inc/hdfs_test.h
#    import/pdclibhdfs/inc/jni_helper.h
#    import/pdclibhdfs/inc/native_mini_dfs.h
#    import/pdclibhdfs/inc/uthash.h
#    import/pdclibhdfs/libhdfs/stdafx.cpp
#    import/pdclibhdfs/libhdfs/stdafx.h
#    import/pdclibhdfs/libhdfs/targetver.h
#    import/pdclibhdfs/src/exception.c
#    import/pdclibhdfs/src/hdfs.c
#    import/pdclibhdfs/src/jni_helper.c
#    import/pdclibhdfs/src/native_mini_dfs.c
#    import/pdclibhdfs/src/test_libhdfs_ops.c
#    import/pdclibhdfs/src/test_libhdfs_read.c
#    import/pdclibhdfs/src/test_libhdfs_threaded.c
#    import/pdclibhdfs/src/test_libhdfs_write.c
#    import/pdclibhdfs/src/test_native_mini_dfs.c
    import/zconf.h
    import/zlib.h
    SNAPLib/AlignerContext.cpp
    SNAPLib/AlignerContext.h
    SNAPLib/AlignerOptions.cpp
    SNAPLib/AlignerOptions.h
    SNAPLib/AlignerStats.cpp
    SNAPLib/AlignerStats.h
    SNAPLib/AlignmentResult.cpp
    SNAPLib/AlignmentResult.h
    SNAPLib/ApproximateCounter.cpp
    SNAPLib/ApproximateCounter.h
    SNAPLib/Bam.cpp
    SNAPLib/Bam.h
    SNAPLib/BaseAligner.cpp
    SNAPLib/BaseAligner.h
        SNAPLib/BaseSeq.cpp
        SNAPLib/BaseSeq.h
    SNAPLib/BiasTables.cpp
    SNAPLib/BigAlloc.cpp
    SNAPLib/BigAlloc.h
    SNAPLib/BufferedAsync.cpp
    SNAPLib/BufferedAsync.h
    SNAPLib/ChimericPairedEndAligner.cpp
    SNAPLib/ChimericPairedEndAligner.h
    SNAPLib/CommandProcessor.cpp
    SNAPLib/CommandProcessor.h
    SNAPLib/Compat.cpp
    SNAPLib/Compat.h
    SNAPLib/DataReader.cpp
    SNAPLib/DataReader.h
    SNAPLib/DataWriter.cpp
    SNAPLib/DataWriter.h
    SNAPLib/directions.h
    SNAPLib/Error.cpp
    SNAPLib/Error.h
    SNAPLib/exit.cpp
    SNAPLib/exit.h
    SNAPLib/FASTA.cpp
    SNAPLib/FASTA.h
    SNAPLib/FASTQ.cpp
    SNAPLib/FASTQ.h
    SNAPLib/FileFormat.h
    SNAPLib/FixedSizeMap.h
    SNAPLib/FixedSizeSet.h
    SNAPLib/FixedSizeVector.h
    SNAPLib/GenericFile.cpp
    SNAPLib/GenericFile.h
    SNAPLib/GenericFile_Blob.cpp
    SNAPLib/GenericFile_Blob.h
    SNAPLib/GenericFile_HDFS.cpp
    SNAPLib/GenericFile_HDFS.h
    SNAPLib/GenericFile_map.cpp
    SNAPLib/GenericFile_map.h
    SNAPLib/GenericFile_stdio.cpp
    SNAPLib/GenericFile_stdio.h
    SNAPLib/Genome.cpp
    SNAPLib/Genome.h
    SNAPLib/GenomeIndex.cpp
    SNAPLib/GenomeIndex.h
    SNAPLib/GzipDataWriter.cpp
    SNAPLib/GzipDataWriter.h
    SNAPLib/HashTable.cpp
    SNAPLib/HashTable.h
    SNAPLib/Histogram.cpp
    SNAPLib/Histogram.h
    SNAPLib/IntersectingPairedEndAligner.cpp
    SNAPLib/IntersectingPairedEndAligner.h
    SNAPLib/LandauVishkin.cpp
    SNAPLib/LandauVishkin.h
    SNAPLib/mapq.cpp
    SNAPLib/mapq.h
    SNAPLib/MultiInputReadSupplier.cpp
    SNAPLib/MultiInputReadSupplier.h
    SNAPLib/options.h
    SNAPLib/PairedAligner.cpp
    SNAPLib/PairedAligner.h
    SNAPLib/PairedEndAligner.h
    SNAPLib/PairedReadMatcher.cpp
    SNAPLib/ParallelTask.cpp
    SNAPLib/ParallelTask.h
    SNAPLib/PriorityQueue.h
    SNAPLib/ProbabilityDistance.cpp
    SNAPLib/ProbabilityDistance.h
    SNAPLib/RangeSplitter.cpp
    SNAPLib/RangeSplitter.h
    SNAPLib/Read.cpp
    SNAPLib/Read.h
    SNAPLib/ReadReader.cpp
    SNAPLib/ReadSupplierQueue.cpp
    SNAPLib/ReadSupplierQueue.h
    SNAPLib/ReadWriter.cpp
    SNAPLib/SAM.cpp
    SNAPLib/SAM.h
    SNAPLib/Seed.cpp
    SNAPLib/Seed.h
    SNAPLib/SeedSequencer.cpp
    SNAPLib/SeedSequencer.h
    SNAPLib/SingleAligner.cpp
    SNAPLib/SingleAligner.h
    SNAPLib/SortedDataWriter.cpp
    SNAPLib/stdafx.cpp
    SNAPLib/stdafx.h
    SNAPLib/Tables.cpp
    SNAPLib/Tables.h
    SNAPLib/targetver.h
    SNAPLib/TestBaseSequence.cpp
    SNAPLib/Util.cpp
    SNAPLib/Util.h
    SNAPLib/VariableSizeMap.h
    SNAPLib/VariableSizeVector.h
    SNAPLib/WindowsFileMapper.h
#    tests/EventTest.cpp
#    tests/LandauVishkinTest.cpp
#    tests/main.cpp
#    tests/ProbabilityDistanceTest.cpp
#    tests/TestLib.cpp
#    tests/TestLib.h
        )

add_executable(snap ${SOURCE_FILES})
target_link_libraries(snap -lz)