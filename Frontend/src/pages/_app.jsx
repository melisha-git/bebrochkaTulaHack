import '@/styles/globals.css'
import { QueryClient, QueryClientProvider } from '@tanstack/react-query'
import { store } from '@/store/store.js'
import { Provider } from 'react-redux'
import Head from 'next/head'

const queryClient = new QueryClient({
	defaultOptions: {
		queries: {
			refetchOnWindowFocus: false
		}
	}
})
export default function App({ Component, pageProps }) {
	return (
		<>
			<Head>
				<title>IWENT</title>
			</Head>
			<Provider store={store}>
				<QueryClientProvider client={queryClient}>
					<Component {...pageProps} />
				</QueryClientProvider>
			</Provider>
		</>
	)
}
