export default function Window({ children }) {
	return (
		<div className='fixed bottom-0  left-0 right-0  lg:top-5 lg:right-auto lg:bottom-5 lg:left-5 lg:w-[400px]'>
			<div className='bg-white rounded-t-3xl lg:rounded-xl px-3 pt-3 '>
				{children}
			</div>
		</div>
	)
}
