Pod::Spec.new do |s|
  s.name         = "ILGAsserts"
  s.version      = "1.1.0"
  s.summary      = "Assert macros for use with XCTest"
  s.homepage     = "https://github.com/ilg/ILGAsserts"
  s.license      = { :type => "MIT", :file => "LICENSE" }
  s.author             = { "Isaac Greenspan" => "ilg@2718.us" }
  s.source       = { :git => "https://github.com/ilg/ILGAsserts.git", :tag => "1.1.0" }
  s.source_files = "ILGAsserts.{h,m}"
  s.framework    = "XCTest"
  s.requires_arc = true
end
